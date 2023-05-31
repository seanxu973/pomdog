// Copyright mogemimi. Distributed under the MIT license.

#pragma once

#include "pomdog/basic/conditional_compilation.h"

POMDOG_SUPPRESS_WARNINGS_GENERATED_BY_STD_HEADERS_BEGIN
#include <cstdint>
POMDOG_SUPPRESS_WARNINGS_GENERATED_BY_STD_HEADERS_END

namespace pomdog::gpu::detail {

enum class BufferBindMode : std::uint8_t {
    ConstantBuffer,
    IndexBuffer,
    VertexBuffer,
};

} // namespace pomdog::gpu::detail
