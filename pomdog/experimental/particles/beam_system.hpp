// Copyright (c) 2013-2021 mogemimi. Distributed under the MIT license.

#pragma once

#include "pomdog/application/duration.hpp"
#include "pomdog/basic/conditional_compilation.hpp"
#include "pomdog/experimental/particles/beam.hpp"
#include "pomdog/experimental/particles/beam_branching.hpp"
#include "pomdog/experimental/particles/beam_emitter.hpp"
#include "pomdog/experimental/random/xoroshiro128_star_star.hpp"
#include "pomdog/math/vector2.hpp"

POMDOG_SUPPRESS_WARNINGS_GENERATED_BY_STD_HEADERS_BEGIN
#include <cstdint>
#include <random>
#include <vector>
POMDOG_SUPPRESS_WARNINGS_GENERATED_BY_STD_HEADERS_END

namespace Pomdog {

class BeamSystem final {
public:
    BeamSystem();

    void Update(const Duration& frameDuration, const Vector2& emitterPosition, const Vector2& target);

    static Vector2 CreateTarget(
        const Vector2& emitterPosition,
        const Radian<float>& emitterRotation,
        float distance);

public:
    BeamEmitter emitter;
    BeamBranching branching;

    std::vector<Beam> beams;

private:
    Duration erapsedTime;
    Duration emissionTimer;
    Random::Xoroshiro128StarStar random;
};

} // namespace Pomdog