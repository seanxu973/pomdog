// Copyright mogemimi. Distributed under the MIT license.

#pragma once

#include "pomdog/input/backends/gamepad_mappings.h"
#include "pomdog/input/gamepad.h"
#include "pomdog/input/gamepad_capabilities.h"
#include "pomdog/input/gamepad_state.h"
#include <array>
#include <cstdint>
#include <memory>

namespace pomdog::detail::linux {

struct ThumbStickInfo final {
    std::int32_t Minimum = 0;
    std::int32_t Range = 0;
    std::int32_t InvertDirection = 1;
};

class GamepadDevice final {
public:
    int fd = -1;
    int deviceEventIndex = -1;
    GamepadCapabilities caps;
    GamepadState state;
    GamepadMappings mappings;
    std::array<int8_t, 32> keyMap;
    std::array<ThumbStickInfo, 6> thumbStickInfos;
    PlayerIndex playerIndex;

public:
    bool Open(int deviceIndex);

    void Close();

    bool HasFileDescriptor() const;

    bool PollEvents();
};

class GamepadLinux final : public Gamepad {
public:
    GamepadLinux() noexcept;

    ~GamepadLinux() override;

    GamepadCapabilities GetCapabilities(PlayerIndex index) const override;

    GamepadState GetState(PlayerIndex index) const override;

    void EnumerateDevices();

    void PollEvents();

private:
    std::array<GamepadDevice, 4> gamepads;
};

} // namespace pomdog::detail::linux