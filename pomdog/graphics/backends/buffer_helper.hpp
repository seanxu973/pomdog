// Copyright (c) 2013-2021 mogemimi. Distributed under the MIT license.

#pragma once

#include "pomdog/basic/conditional_compilation.hpp"
#include "pomdog/graphics/forward_declarations.hpp"

POMDOG_SUPPRESS_WARNINGS_GENERATED_BY_STD_HEADERS_BEGIN
#include <cstdint>
#include <cstdlib>
POMDOG_SUPPRESS_WARNINGS_GENERATED_BY_STD_HEADERS_END

namespace Pomdog::Detail::BufferHelper {

std::size_t ToIndexElementOffsetBytes(IndexElementSize elementSize) noexcept;

std::uint16_t ToByteSize(InputElementFormat format) noexcept;

} // namespace Pomdog::Detail::BufferHelper