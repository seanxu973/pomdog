// Copyright mogemimi. Distributed under the MIT license.

#pragma once

#include "pomdog/basic/conditional_compilation.h"
#include "pomdog/basic/export.h"
#include "pomdog/gpu/shader_pipeline_stage.h"

POMDOG_SUPPRESS_WARNINGS_GENERATED_BY_STD_HEADERS_BEGIN
#include <cstddef>
#include <memory>
#include <optional>
#include <string>
#include <tuple>
POMDOG_SUPPRESS_WARNINGS_GENERATED_BY_STD_HEADERS_END

namespace pomdog {
class Error;
class GraphicsDevice;
class Shader;
} // namespace pomdog

namespace pomdog::ShaderCompilers::GLSLCompiler {

/// Creates a shader from a string of source code.
[[nodiscard]] POMDOG_EXPORT std::tuple<std::unique_ptr<Shader>, std::unique_ptr<Error>>
CreateShader(
    GraphicsDevice& graphicsDevice,
    const void* shaderSource,
    std::size_t byteLength,
    ShaderPipelineStage pipelineStage,
    std::optional<std::string>&& currentDirectory);

} // namespace pomdog::ShaderCompilers::GLSLCompiler
