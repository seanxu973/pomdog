// Copyright mogemimi. Distributed under the MIT license.

#pragma once

#include "pomdog/basic/conditional_compilation.h"
#include "pomdog/gpu/input_classification.h"
#include "pomdog/gpu/input_element_format.h"

POMDOG_SUPPRESS_WARNINGS_GENERATED_BY_STD_HEADERS_BEGIN
#include <cstdint>
POMDOG_SUPPRESS_WARNINGS_GENERATED_BY_STD_HEADERS_END

namespace pomdog::gpu {

struct InputElement final {
    std::uint16_t ByteOffset;
    std::uint16_t InputSlot;
    InputElementFormat Format;
    InputClassification InputSlotClass;
    std::uint16_t InstanceStepRate;
};

} // namespace pomdog::gpu