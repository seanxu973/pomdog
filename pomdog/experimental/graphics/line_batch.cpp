// Copyright (c) 2013-2021 mogemimi. Distributed under the MIT license.

#include "pomdog/experimental/graphics/line_batch.hpp"
#include "pomdog/basic/conditional_compilation.hpp"
#include "pomdog/content/asset_builders/pipeline_state_builder.hpp"
#include "pomdog/content/asset_builders/shader_builder.hpp"
#include "pomdog/content/asset_manager.hpp"
#include "pomdog/graphics/blend_description.hpp"
#include "pomdog/graphics/buffer_usage.hpp"
#include "pomdog/graphics/constant_buffer.hpp"
#include "pomdog/graphics/depth_stencil_description.hpp"
#include "pomdog/graphics/graphics_command_list.hpp"
#include "pomdog/graphics/graphics_device.hpp"
#include "pomdog/graphics/input_layout_helper.hpp"
#include "pomdog/graphics/pipeline_state.hpp"
#include "pomdog/graphics/presentation_parameters.hpp"
#include "pomdog/graphics/primitive_topology.hpp"
#include "pomdog/graphics/shader.hpp"
#include "pomdog/graphics/vertex_buffer.hpp"
#include "pomdog/math/bounding_box.hpp"
#include "pomdog/math/color.hpp"
#include "pomdog/math/math.hpp"
#include "pomdog/math/matrix3x2.hpp"
#include "pomdog/math/matrix4x4.hpp"
#include "pomdog/math/rectangle.hpp"
#include "pomdog/math/vector2.hpp"
#include "pomdog/math/vector3.hpp"
#include "pomdog/math/vector4.hpp"

POMDOG_SUPPRESS_WARNINGS_GENERATED_BY_STD_HEADERS_BEGIN
#include <algorithm>
#include <cmath>
#include <cstring>
POMDOG_SUPPRESS_WARNINGS_GENERATED_BY_STD_HEADERS_END

namespace Pomdog {
namespace {

// Built-in shaders
#include "shaders/glsl.embedded/line_batch_ps.inc.hpp"
#include "shaders/glsl.embedded/line_batch_vs.inc.hpp"
#include "shaders/hlsl.embedded/line_batch_ps.inc.hpp"
#include "shaders/hlsl.embedded/line_batch_vs.inc.hpp"
#include "shaders/metal.embedded/line_batch.inc.hpp"

} // namespace

// MARK: - LineBatch::Impl

class LineBatch::Impl {
public:
    static constexpr std::size_t MaxVertexCount = 4096;
    static constexpr std::size_t MinVertexCount = 256;

    struct Vertex {
        // {xyz} = position.xyz
        Vector3 Position;

        // {xyzw} = color.rgba
        Vector4 Color;
    };

    std::vector<Vertex> vertices;

private:
    std::shared_ptr<GraphicsCommandList> commandList;
    std::shared_ptr<VertexBuffer> vertexBuffer;
    std::shared_ptr<PipelineState> pipelineState;
    std::shared_ptr<ConstantBuffer> constantBuffer;

public:
    Impl(
        const std::shared_ptr<GraphicsDevice>& graphicsDevice,
        AssetManager& assets);

    void Begin(
        const std::shared_ptr<GraphicsCommandList>& commandListIn,
        const Matrix4x4& transformMatrix);

    void DrawLine(
        const Vector2& point1, const Vector2& point2,
        const Vector4& color1, const Vector4& color2);

    void DrawLine(
        const Vector3& point1, const Vector3& point2,
        const Vector4& color1, const Vector4& color2);

    void DrawTriangle(
        const Vector2& point1, const Vector2& point2, const Vector2& point3,
        const Vector4& color1, const Vector4& color2, const Vector4& color3);

    void End();

    void Flush();
};

LineBatch::Impl::Impl(
    const std::shared_ptr<GraphicsDevice>& graphicsDevice,
    AssetManager& assets)
{
    vertices.reserve(MinVertexCount);
    {
        auto maxVertexCount = MaxVertexCount;

        vertexBuffer = std::get<0>(graphicsDevice->CreateVertexBuffer(
            maxVertexCount,
            sizeof(Vertex),
            BufferUsage::Dynamic));
    }
    {
        auto inputLayout = InputLayoutHelper{}
            .Float3().Float4();

        auto vertexShaderBuilder = assets.CreateBuilder<Shader>(ShaderPipelineStage::VertexShader)
            .SetGLSL(Builtin_GLSL_LineBatch_VS, std::strlen(Builtin_GLSL_LineBatch_VS))
            .SetHLSLPrecompiled(BuiltinHLSL_LineBatch_VS, sizeof(BuiltinHLSL_LineBatch_VS))
            .SetMetal(Builtin_Metal_LineBatch, std::strlen(Builtin_Metal_LineBatch), "LineBatchVS");

        auto pixelShaderBuilder = assets.CreateBuilder<Shader>(ShaderPipelineStage::PixelShader)
            .SetGLSL(Builtin_GLSL_LineBatch_PS, std::strlen(Builtin_GLSL_LineBatch_PS))
            .SetHLSLPrecompiled(BuiltinHLSL_LineBatch_PS, sizeof(BuiltinHLSL_LineBatch_PS))
            .SetMetal(Builtin_Metal_LineBatch, std::strlen(Builtin_Metal_LineBatch), "LineBatchPS");

        auto [vertexShader, vertexShaderErr] = vertexShaderBuilder.Build();
        if (vertexShaderErr != nullptr) {
            // FIXME: error handling
        }

        auto [pixelShader, pixelShaderErr] = pixelShaderBuilder.Build();
        if (pixelShaderErr != nullptr) {
            // FIXME: error handling
        }

        auto presentationParameters = graphicsDevice->GetPresentationParameters();

        std::unique_ptr<Error> pipelineStateErr;
        std::tie(pipelineState, pipelineStateErr) = assets.CreateBuilder<PipelineState>()
            .SetRenderTargetViewFormat(presentationParameters.BackBufferFormat)
            .SetDepthStencilViewFormat(presentationParameters.DepthStencilFormat)
            .SetVertexShader(std::move(vertexShader))
            .SetPixelShader(std::move(pixelShader))
            .SetInputLayout(inputLayout.CreateInputLayout())
            .SetPrimitiveTopology(PrimitiveTopology::LineList)
            .SetBlendState(BlendDescription::CreateNonPremultiplied())
            .SetDepthStencilState(DepthStencilDescription::CreateDefault())
            .SetConstantBufferBindSlot("TransformMatrix", 0)
            .Build();
        if (pipelineStateErr != nullptr) {
            // FIXME: error handling
        }
    }

    constantBuffer = std::get<0>(graphicsDevice->CreateConstantBuffer(
        sizeof(Matrix4x4),
        BufferUsage::Dynamic));
}

void LineBatch::Impl::Begin(
    const std::shared_ptr<GraphicsCommandList>& commandListIn,
    const Matrix4x4& transformMatrix)
{
    POMDOG_ASSERT(commandListIn);
    commandList = commandListIn;

    alignas(16) Matrix4x4 transposedMatrix = Matrix4x4::Transpose(transformMatrix);
    constantBuffer->SetValue(transposedMatrix);
}

void LineBatch::Impl::End()
{
    if (vertices.empty()) {
        return;
    }

    Flush();
    commandList.reset();
}

void LineBatch::Impl::Flush()
{
    POMDOG_ASSERT(!vertices.empty());
    POMDOG_ASSERT(vertices.size() <= MaxVertexCount);
    vertexBuffer->SetData(vertices.data(), vertices.size());

    commandList->SetVertexBuffer(0, vertexBuffer);
    commandList->SetPipelineState(pipelineState);
    commandList->SetConstantBuffer(0, constantBuffer);
    commandList->Draw(vertices.size(), 0);

    vertices.clear();
}

void LineBatch::Impl::DrawLine(
    const Vector2& point1, const Vector2& point2,
    const Vector4& color1, const Vector4& color2)
{
    if (vertices.size() + 2 > MaxVertexCount) {
        Flush();
    }

    POMDOG_ASSERT(vertices.size() + 2 <= Impl::MaxVertexCount);
    vertices.push_back(Vertex{Vector3(point1, 0.0f), color1});
    vertices.push_back(Vertex{Vector3(point2, 0.0f), color2});
}

void LineBatch::Impl::DrawLine(
    const Vector3& point1, const Vector3& point2,
    const Vector4& color1, const Vector4& color2)
{
    if (vertices.size() + 2 > MaxVertexCount) {
        Flush();
    }

    POMDOG_ASSERT(vertices.size() + 2 <= Impl::MaxVertexCount);
    vertices.push_back(Vertex{point1, color1});
    vertices.push_back(Vertex{point2, color2});
}

void LineBatch::Impl::DrawTriangle(
    const Vector2& point1, const Vector2& point2, const Vector2& point3,
    const Vector4& color1, const Vector4& color2, const Vector4& color3)
{
    if (vertices.size() + 6 > MaxVertexCount) {
        Flush();
    }

    POMDOG_ASSERT(vertices.size() + 6 <= Impl::MaxVertexCount);
    vertices.push_back(Vertex{Vector3(point1, 0.0f), color1});
    vertices.push_back(Vertex{Vector3(point2, 0.0f), color2});
    vertices.push_back(Vertex{Vector3(point2, 0.0f), color2});
    vertices.push_back(Vertex{Vector3(point3, 0.0f), color3});
    vertices.push_back(Vertex{Vector3(point3, 0.0f), color3});
    vertices.push_back(Vertex{Vector3(point1, 0.0f), color1});
}

// MARK: - LineBatch

LineBatch::LineBatch(
    const std::shared_ptr<GraphicsDevice>& graphicsDevice,
    AssetManager& assets)
    : impl(std::make_unique<Impl>(graphicsDevice, assets))
{
}

LineBatch::~LineBatch() = default;

void LineBatch::Begin(
    const std::shared_ptr<GraphicsCommandList>& commandListIn,
    const Matrix4x4& transformMatrixIn)
{
    POMDOG_ASSERT(impl);
    impl->Begin(commandListIn, transformMatrixIn);
}

void LineBatch::End()
{
    POMDOG_ASSERT(impl);
    impl->End();
}

void LineBatch::DrawBox(const BoundingBox& box, const Color& color)
{
    this->DrawBox(box.Min, box.Max - box.Min, Vector3::Zero, color);
}

void LineBatch::DrawBox(
    const Vector3& position,
    const Vector3& scale,
    const Color& color)
{
    this->DrawBox(position, scale, Vector3::Zero, color);
}

void LineBatch::DrawBox(
    const Vector3& position,
    const Vector3& scale,
    const Vector3& originPivot,
    const Color& color)
{
    POMDOG_ASSERT(impl);

    Vector3 boxVertices[] = {
        Vector3{0.0f, 0.0f, 0.0f},
        Vector3{0.0f, 0.0f, 1.0f},
        Vector3{0.0f, 1.0f, 0.0f},
        Vector3{0.0f, 1.0f, 1.0f},
        Vector3{1.0f, 0.0f, 0.0f},
        Vector3{1.0f, 0.0f, 1.0f},
        Vector3{1.0f, 1.0f, 0.0f},
        Vector3{1.0f, 1.0f, 1.0f},
    };

    for (auto& v : boxVertices) {
        v = ((v - originPivot) * scale) + position;
    }

    const auto colorVector = color.ToVector4();
    auto draw = [&](int a, int b) {
        impl->DrawLine(
            boxVertices[a],
            boxVertices[b],
            colorVector,
            colorVector);
    };

    draw(0, 1);
    draw(0, 2);
    draw(2, 3);
    draw(3, 1);
    draw(4, 5);
    draw(4, 6);
    draw(6, 7);
    draw(7, 5);
    draw(0, 4);
    draw(2, 6);
    draw(3, 7);
    draw(1, 5);
}

void LineBatch::DrawCircle(const Vector2& position, float radius, const Color& color, int segments)
{
    POMDOG_ASSERT(impl);
    POMDOG_ASSERT(segments >= 3);
    POMDOG_ASSERT(radius >= 0);

    if (radius <= 0) {
        return;
    }

    POMDOG_ASSERT(radius > 0);

    POMDOG_ASSERT(segments >= 3);
    Radian<float> centralAngle = Math::TwoPi<float> / segments;
    Vector2 prevPoint = position + Vector2{radius, 0};

    auto colorVector = color.ToVector4();

    for (int i = 0; i < segments; ++i) {
        auto rad = centralAngle * static_cast<float>(i + 1);
        auto cos = std::cos(rad.value);
        auto sin = std::sin(rad.value);
        auto nextPoint = position + (radius * Vector2{cos, sin});
        impl->DrawLine(nextPoint, prevPoint, colorVector, colorVector);
        prevPoint = nextPoint;
    }
}

void LineBatch::DrawLine(const Vector2& start, const Vector2& end, const Color& color)
{
    POMDOG_ASSERT(impl);
    auto colorVector = color.ToVector4();
    impl->DrawLine(start, end, colorVector, colorVector);
}

void LineBatch::DrawLine(const Vector2& start, const Vector2& end, const Color& startColor, const Color& endColor)
{
    POMDOG_ASSERT(impl);
    auto colorVector1 = startColor.ToVector4();
    auto colorVector2 = endColor.ToVector4();
    impl->DrawLine(start, end, colorVector1, colorVector2);
}

void LineBatch::DrawLine(const Vector3& start, const Vector3& end, const Color& color)
{
    POMDOG_ASSERT(impl);
    auto colorVector = color.ToVector4();
    impl->DrawLine(start, end, colorVector, colorVector);
}

void LineBatch::DrawLine(const Vector3& start, const Vector3& end, const Color& startColor, const Color& endColor)
{
    POMDOG_ASSERT(impl);
    auto colorVector1 = startColor.ToVector4();
    auto colorVector2 = endColor.ToVector4();
    impl->DrawLine(start, end, colorVector1, colorVector2);
}

void LineBatch::DrawRectangle(const Rectangle& sourceRect, const Color& color)
{
    POMDOG_ASSERT(impl);
    DrawRectangle(sourceRect, color, color, color, color);
}

void LineBatch::DrawRectangle(const Rectangle& sourceRect,
    const Color& color1, const Color& color2, const Color& color3, const Color& color4)
{
    POMDOG_ASSERT(impl);

    if (sourceRect.Width <= 0 || sourceRect.Height <= 0) {
        return;
    }

    std::array<Vector2, 4> rectVertices = {{
        Vector2{static_cast<float>(sourceRect.GetLeft()), static_cast<float>(sourceRect.Y - sourceRect.Height)},
        Vector2{static_cast<float>(sourceRect.GetLeft()), static_cast<float>(sourceRect.Y)},
        Vector2{static_cast<float>(sourceRect.GetRight()), static_cast<float>(sourceRect.Y)},
        Vector2{static_cast<float>(sourceRect.GetRight()), static_cast<float>(sourceRect.Y - sourceRect.Height)},
    }};

    auto colorVector1 = color1.ToVector4();
    auto colorVector2 = color2.ToVector4();
    auto colorVector3 = color3.ToVector4();
    auto colorVector4 = color4.ToVector4();

    impl->DrawLine(rectVertices[0], rectVertices[1], colorVector1, colorVector2);
    impl->DrawLine(rectVertices[1], rectVertices[2], colorVector2, colorVector3);
    impl->DrawLine(rectVertices[2], rectVertices[3], colorVector3, colorVector4);
    impl->DrawLine(rectVertices[3], rectVertices[0], colorVector4, colorVector1);
}

void LineBatch::DrawRectangle(const Matrix3x2& matrix,
    const Rectangle& sourceRect, const Color& color)
{
    POMDOG_ASSERT(impl);

    if (sourceRect.Width <= 0 || sourceRect.Height <= 0) {
        return;
    }

    std::array<Vector2, 4> rectVertices = {{
        Vector2{static_cast<float>(sourceRect.GetLeft()), static_cast<float>(sourceRect.Y - sourceRect.Height)},
        Vector2{static_cast<float>(sourceRect.GetLeft()), static_cast<float>(sourceRect.Y)},
        Vector2{static_cast<float>(sourceRect.GetRight()), static_cast<float>(sourceRect.Y)},
        Vector2{static_cast<float>(sourceRect.GetRight()), static_cast<float>(sourceRect.Y - sourceRect.Height)},
    }};

    for (auto& vertex : rectVertices) {
        vertex = Vector2::Transform(vertex, matrix);
    }

    auto colorVector = color.ToVector4();

    impl->DrawLine(rectVertices[0], rectVertices[1], colorVector, colorVector);
    impl->DrawLine(rectVertices[1], rectVertices[2], colorVector, colorVector);
    impl->DrawLine(rectVertices[2], rectVertices[3], colorVector, colorVector);
    impl->DrawLine(rectVertices[3], rectVertices[0], colorVector, colorVector);
}

void LineBatch::DrawSphere(
    const Vector3& position,
    float radius,
    const Color& color,
    int segments)
{
    POMDOG_ASSERT(impl);
    POMDOG_ASSERT(segments >= 4);
    POMDOG_ASSERT(radius >= 0);

    if (radius <= 0) {
        return;
    }

    const auto rings = std::max(segments, 4);
    const auto sectors = std::max(segments, 4);

    POMDOG_ASSERT(sectors > 0);
    POMDOG_ASSERT(rings > 0);

    std::vector<Vector3> sphereVertices;
    sphereVertices.reserve(sectors * (rings - 1) + 2);

    const auto R = 1.0f / static_cast<float>(rings - 1);
    const auto S = 1.0f / static_cast<float>(sectors - 1);

    // Create sphere vertices
    sphereVertices.push_back(Vector3{0.0f, 1.0f, 0.0f});
    for (int ring = 1; ring < rings; ++ring) {
        const auto latitude = Math::Pi<float> * ring * R;
        const auto y = std::cos(latitude);
        const auto r = std::sin(latitude);
        for (int s = 0; s < sectors; ++s) {
            auto longitude = Math::TwoPi<float> * s * S;
            auto x = r * std::cos(longitude);
            auto z = r * std::sin(longitude);
            sphereVertices.push_back(Vector3{x, y, z});
        }
    }
    sphereVertices.push_back(Vector3{0.0f, -1.0f, 0.0f});

    // Scaling and translation
    for (auto& v : sphereVertices) {
        v = v * radius + position;
    }

    const auto colorVector = color.ToVector4();
    const auto drawIndices = [&](std::size_t a, std::size_t b) {
        POMDOG_ASSERT(a < sphereVertices.size());
        POMDOG_ASSERT(b < sphereVertices.size());
        const auto& start = sphereVertices[a];
        const auto& end = sphereVertices[b];
        impl->DrawLine(start, end, colorVector, colorVector);
    };

    for (int s = 1; s < sectors; ++s) {
        drawIndices(0, s);
    }

    int count = 1;
    for (int s = 2; s < sectors; ++s) {
        for (int ring = 1; ring < rings; ++ring) {
            drawIndices(count, count + 1);
            drawIndices(count, count + sectors);
            ++count;
        }
        POMDOG_ASSERT(count + 1 >= sectors);
        drawIndices(count, (count + 1) - sectors);
        drawIndices(count, count + sectors);
        ++count;
    }

    for (int s = 1; s < sectors; ++s) {
        drawIndices(count, count + 1);
        drawIndices(count, sphereVertices.size() - 1);
        ++count;
    }

    POMDOG_ASSERT(count + 1 >= sectors);
    drawIndices(count, (count + 1) - sectors);
    drawIndices(count, sphereVertices.size() - 1);
}

void LineBatch::DrawTriangle(const Vector2& point1, const Vector2& point2, const Vector2& point3, const Color& color)
{
    POMDOG_ASSERT(impl);
    auto colorVector = color.ToVector4();
    impl->DrawTriangle(point1, point2, point3, colorVector, colorVector, colorVector);
}

void LineBatch::DrawTriangle(
    const Vector2& point1, const Vector2& point2, const Vector2& point3,
    const Color& color1, const Color& color2, const Color& color3)
{
    POMDOG_ASSERT(impl);
    auto colorVector1 = color1.ToVector4();
    auto colorVector2 = color2.ToVector4();
    auto colorVector3 = color3.ToVector4();
    impl->DrawTriangle(point1, point2, point3, colorVector1, colorVector2, colorVector3);
}

} // namespace Pomdog
