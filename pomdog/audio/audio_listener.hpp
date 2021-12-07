// Copyright (c) 2013-2021 mogemimi. Distributed under the MIT license.

#pragma once

#include "pomdog/math/vector3.hpp"

namespace Pomdog {

class AudioListener final {
public:
    Vector3 Forward;
    Vector3 Position;
    Vector3 Up;
    Vector3 Velocity;
};

} // namespace Pomdog