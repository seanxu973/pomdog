// Copyright (c) 2013-2020 mogemimi. Distributed under the MIT license.

#include "Pomdog/Graphics/ShaderCompilers/GLSLCompiler.hpp"
#include "../../Graphics.Backends/ShaderBytecode.hpp"
#include "../../Graphics.Backends/ShaderCompileOptions.hpp"
#include "Pomdog/Graphics/GraphicsDevice.hpp"
#include "Pomdog/Graphics/Shader.hpp"
#include "Pomdog/Graphics/ShaderLanguage.hpp"
#include "Pomdog/Utility/Assert.hpp"

using Pomdog::Detail::ShaderBytecode;
using Pomdog::Detail::ShaderCompileOptions;

namespace Pomdog::ShaderCompilers::GLSLCompiler {

[[nodiscard]] std::tuple<std::unique_ptr<Shader>, std::shared_ptr<Error>>
CreateShader(
    GraphicsDevice& graphicsDevice,
    const void* shaderSource,
    std::size_t byteLength,
    ShaderPipelineStage pipelineStage,
    std::optional<std::string>&& currentDirectory)
{
    POMDOG_ASSERT(shaderSource != nullptr);
    POMDOG_ASSERT(byteLength > 0);
    POMDOG_ASSERT(graphicsDevice.GetSupportedLanguage() == ShaderLanguage::GLSL);

    ShaderBytecode shaderBytecode;
    shaderBytecode.Code = shaderSource;
    shaderBytecode.ByteLength = byteLength;

    ShaderCompileOptions compileOptions;
    compileOptions.EntryPoint = "main";
    compileOptions.Profile.PipelineStage = pipelineStage;
    compileOptions.Precompiled = false;

    if (currentDirectory) {
        compileOptions.CurrentDirectory = std::move(*currentDirectory);
    }

    return graphicsDevice.CreateShader(std::move(shaderBytecode), std::move(compileOptions));
}

} // namespace Pomdog::ShaderCompilers::GLSLCompiler
