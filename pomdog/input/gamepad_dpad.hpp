// Copyright (c) 2013-2021 mogemimi. Distributed under the MIT license.

#pragma once

#include "pomdog/input/button_state.hpp"

namespace Pomdog {

struct GamepadDPad final {
    ButtonState Down = ButtonState::Released;
    ButtonState Up = ButtonState::Released;
    ButtonState Left = ButtonState::Released;
    ButtonState Right = ButtonState::Released;
};

} // namespace Pomdog