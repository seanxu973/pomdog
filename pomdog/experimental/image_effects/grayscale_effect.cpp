// Copyright (c) 2013-2021 mogemimi. Distributed under the MIT license.

#include "pomdog/experimental/image_effects/grayscale_effect.hpp"
#include "pomdog/basic/conditional_compilation.hpp"
#include "pomdog/basic/platform.hpp"
#include "pomdog/content/asset_builders/pipeline_state_builder.hpp"
#include "pomdog/content/asset_builders/shader_builder.hpp"
#include "pomdog/graphics/blend_description.hpp"
#include "pomdog/graphics/constant_buffer.hpp"
#include "pomdog/graphics/depth_stencil_description.hpp"
#include "pomdog/graphics/graphics_command_list.hpp"
#include "pomdog/graphics/graphics_device.hpp"
#include "pomdog/graphics/input_layout_helper.hpp"
#include "pomdog/graphics/pipeline_state.hpp"
#include "pomdog/graphics/presentation_parameters.hpp"
#include "pomdog/graphics/primitive_topology.hpp"
#include "pomdog/graphics/render_target2d.hpp"
#include "pomdog/graphics/sampler_state.hpp"
#include "pomdog/graphics/shader.hpp"
#include "pomdog/utility/assert.hpp"

POMDOG_SUPPRESS_WARNINGS_GENERATED_BY_STD_HEADERS_BEGIN
#include <cstring>
POMDOG_SUPPRESS_WARNINGS_GENERATED_BY_STD_HEADERS_END

namespace Pomdog {
namespace {

// Built-in shaders
#if defined(POMDOG_PLATFORM_WIN32) || \
    defined(POMDOG_PLATFORM_LINUX) || \
    defined(POMDOG_PLATFORM_MACOSX) || \
    defined(POMDOG_PLATFORM_EMSCRIPTEN)
#include "shaders/glsl.embedded/grayscale_ps.inc.hpp"
#include "shaders/glsl.embedded/screen_quad_vs.inc.hpp"
#endif
#if defined(POMDOG_PLATFORM_WIN32)
#include "shaders/hlsl.embedded/grayscale_ps.inc.hpp"
#include "shaders/hlsl.embedded/screen_quad_vs.inc.hpp"
#endif
#if defined(POMDOG_PLATFORM_MACOSX)
#include "shaders/metal.embedded/grayscale_ps.inc.hpp"
#include "shaders/metal.embedded/screen_quad_vs.inc.hpp"
#endif

} // namespace

GrayscaleEffect::GrayscaleEffect(
    const std::shared_ptr<GraphicsDevice>& graphicsDevice,
    AssetManager& assets)
{
    samplerLinear = std::get<0>(graphicsDevice->CreateSamplerState(
        SamplerDescription::CreateLinearWrap()));

    auto inputLayout = InputLayoutHelper{}
        .Float3().Float2();

    auto vertexShaderBuilder = assets.CreateBuilder<Shader>(ShaderPipelineStage::VertexShader);
    auto pixelShaderBuilder = assets.CreateBuilder<Shader>(ShaderPipelineStage::PixelShader);

#if defined(POMDOG_PLATFORM_WIN32) || \
    defined(POMDOG_PLATFORM_LINUX) || \
    defined(POMDOG_PLATFORM_MACOSX) || \
    defined(POMDOG_PLATFORM_EMSCRIPTEN)
    vertexShaderBuilder.SetGLSL(Builtin_GLSL_ScreenQuad_VS, std::strlen(Builtin_GLSL_ScreenQuad_VS));
    pixelShaderBuilder.SetGLSL(Builtin_GLSL_Grayscale_PS, std::strlen(Builtin_GLSL_Grayscale_PS));
#endif
#if defined(POMDOG_PLATFORM_WIN32)
    vertexShaderBuilder.SetHLSLPrecompiled(BuiltinHLSL_ScreenQuad_VS, sizeof(BuiltinHLSL_ScreenQuad_VS));
    pixelShaderBuilder.SetHLSLPrecompiled(BuiltinHLSL_Grayscale_PS, sizeof(BuiltinHLSL_Grayscale_PS));
#endif
#if defined(POMDOG_PLATFORM_MACOSX)
    vertexShaderBuilder.SetMetal(Builtin_Metal_ScreenQuad_VS, std::strlen(Builtin_Metal_ScreenQuad_VS), "ScreenQuadVS");
    pixelShaderBuilder.SetMetal(Builtin_Metal_Grayscale_PS, std::strlen(Builtin_Metal_Grayscale_PS), "GrayscalePS");
#endif

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
        .SetPrimitiveTopology(PrimitiveTopology::TriangleList)
        .SetBlendState(BlendDescription::CreateOpaque())
        .SetDepthStencilState(DepthStencilDescription::CreateNone())
        .SetConstantBufferBindSlot("ImageEffectConstants", 0)
        .Build();
    if (pipelineStateErr != nullptr) {
        // FIXME: error handling
    }
}

void GrayscaleEffect::Apply(
    GraphicsCommandList& commandList,
    const std::shared_ptr<RenderTarget2D>& source,
    const std::shared_ptr<ConstantBuffer>& constantBuffer)
{
    POMDOG_ASSERT(source);
    POMDOG_ASSERT(constantBuffer);
    commandList.SetConstantBuffer(0, constantBuffer);
    commandList.SetSamplerState(0, samplerLinear);
    commandList.SetTexture(0, source);
    commandList.SetPipelineState(pipelineState);
}

} // namespace Pomdog
