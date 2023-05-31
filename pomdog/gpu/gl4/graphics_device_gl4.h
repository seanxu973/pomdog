// Copyright mogemimi. Distributed under the MIT license.

#pragma once

#include "pomdog/basic/conditional_compilation.h"
#include "pomdog/gpu/graphics_device.h"
#include "pomdog/gpu/presentation_parameters.h"
#include "pomdog/utility/errors.h"

POMDOG_SUPPRESS_WARNINGS_GENERATED_BY_STD_HEADERS_BEGIN
#include <memory>
POMDOG_SUPPRESS_WARNINGS_GENERATED_BY_STD_HEADERS_END

namespace pomdog::gpu::detail::gl4 {

class GraphicsDeviceGL4 final : public GraphicsDevice {
public:
    [[nodiscard]] std::unique_ptr<Error>
    initialize(const PresentationParameters& presentationParameters) noexcept;

    /// Gets the currently supported shader language.
    [[nodiscard]] ShaderLanguage
    getSupportedLanguage() const noexcept override;

    /// Gets the presentation parameters.
    [[nodiscard]] PresentationParameters
    getPresentationParameters() const noexcept override;

    /// Creates a graphics command list.
    [[nodiscard]] std::tuple<std::shared_ptr<CommandList>, std::unique_ptr<Error>>
    createCommandList() noexcept override;

    /// Creates a vertex buffer.
    [[nodiscard]] std::tuple<std::shared_ptr<VertexBuffer>, std::unique_ptr<Error>>
    createVertexBuffer(
        const void* vertices,
        std::size_t vertexCount,
        std::size_t strideBytes,
        BufferUsage bufferUsage) noexcept override;

    /// Creates a vertex buffer.
    [[nodiscard]] std::tuple<std::shared_ptr<VertexBuffer>, std::unique_ptr<Error>>
    createVertexBuffer(
        std::size_t vertexCount,
        std::size_t strideBytes,
        BufferUsage bufferUsage) noexcept override;

    /// Creates an index buffer.
    [[nodiscard]] std::tuple<std::shared_ptr<IndexBuffer>, std::unique_ptr<Error>>
    createIndexBuffer(
        IndexFormat elementSize,
        const void* indices,
        std::size_t indexCount,
        BufferUsage bufferUsage) noexcept override;

    /// Creates an index buffer.
    [[nodiscard]] std::tuple<std::shared_ptr<IndexBuffer>, std::unique_ptr<Error>>
    createIndexBuffer(
        IndexFormat elementSize,
        std::size_t indexCount,
        BufferUsage bufferUsage) noexcept override;

    /// Creates a constant buffer.
    [[nodiscard]] std::tuple<std::shared_ptr<ConstantBuffer>, std::unique_ptr<Error>>
    createConstantBuffer(
        const void* sourceData,
        std::size_t sizeInBytes,
        BufferUsage bufferUsage) noexcept override;

    /// Creates a constant buffer.
    [[nodiscard]] std::tuple<std::shared_ptr<ConstantBuffer>, std::unique_ptr<Error>>
    createConstantBuffer(
        std::size_t sizeInBytes,
        BufferUsage bufferUsage) noexcept override;

    /// Creates a pipeline state object.
    [[nodiscard]] std::tuple<std::shared_ptr<PipelineState>, std::unique_ptr<Error>>
    createPipelineState(const PipelineDescriptor& descriptor) noexcept override;

    /// Creates an effect reflection.
    [[nodiscard]] std::tuple<std::shared_ptr<EffectReflection>, std::unique_ptr<Error>>
    createEffectReflection(
        const PipelineDescriptor& descriptor,
        const std::shared_ptr<PipelineState>& pipelineState) noexcept override;

    /// Creates a shader object.
    [[nodiscard]] std::tuple<std::unique_ptr<Shader>, std::unique_ptr<Error>>
    createShader(
        const detail::ShaderBytecode& shaderBytecode,
        const detail::ShaderCompileOptions& compileOptions) noexcept override;

    /// Creates a 2D render target.
    [[nodiscard]] std::tuple<std::shared_ptr<RenderTarget2D>, std::unique_ptr<Error>>
    createRenderTarget2D(
        std::int32_t width,
        std::int32_t height) noexcept override;

    /// Creates a 2D render target.
    [[nodiscard]] std::tuple<std::shared_ptr<RenderTarget2D>, std::unique_ptr<Error>>
    createRenderTarget2D(
        std::int32_t width,
        std::int32_t height,
        bool generateMipmap,
        PixelFormat format) noexcept override;

    /// Creates a depth stencil buffer.
    [[nodiscard]] std::tuple<std::shared_ptr<DepthStencilBuffer>, std::unique_ptr<Error>>
    createDepthStencilBuffer(
        std::int32_t width,
        std::int32_t height,
        PixelFormat depthStencilFormat) noexcept override;

    /// Creates a sampler state object.
    [[nodiscard]] std::tuple<std::shared_ptr<SamplerState>, std::unique_ptr<Error>>
    createSamplerState(const SamplerDescriptor& descriptor) noexcept override;

    /// Creates a 2D texture.
    [[nodiscard]] std::tuple<std::shared_ptr<gpu::Texture2D>, std::unique_ptr<Error>>
    createTexture2D(
        std::int32_t width,
        std::int32_t height) noexcept override;

    /// Creates a 2D texture.
    [[nodiscard]] std::tuple<std::shared_ptr<gpu::Texture2D>, std::unique_ptr<Error>>
    createTexture2D(
        std::int32_t width,
        std::int32_t height,
        bool mipMap,
        PixelFormat format) noexcept override;

    void clientSizeChanged(int width, int height);

private:
    PresentationParameters presentationParameters;
};

} // namespace pomdog::gpu::detail::gl4
