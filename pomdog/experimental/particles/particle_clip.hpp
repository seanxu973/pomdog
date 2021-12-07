// Copyright (c) 2013-2021 mogemimi. Distributed under the MIT license.

#pragma once

#include "pomdog/application/duration.hpp"
#include "pomdog/basic/conditional_compilation.hpp"
#include "pomdog/experimental/particles/emitter_shapes/particle_emitter_shape.hpp"
#include "pomdog/experimental/particles/parameters/particle_parameter.hpp"
#include "pomdog/math/color.hpp"
#include "pomdog/math/radian.hpp"

POMDOG_SUPPRESS_WARNINGS_GENERATED_BY_STD_HEADERS_BEGIN
#include <cstdint>
#include <memory>
POMDOG_SUPPRESS_WARNINGS_GENERATED_BY_STD_HEADERS_END

namespace Pomdog {

class ParticleClip final {
public:
    Pomdog::Duration Duration = std::chrono::seconds{5};

    int EmissionRate = 16;

    int EmissionRateOverTime = 16;

    int MaxParticles = 128;

    /// The initial life time in seconds for particles.
    float StartLifetime = 1.0f;

    ///@note StartSpeed (pixel/second)
    std::unique_ptr<Detail::Particles::ParticleParameter<float>> StartSpeed;

    std::unique_ptr<Detail::Particles::ParticleEmitterShape> Shape;

    std::unique_ptr<Detail::Particles::ParticleParameter<Color>> StartColor;

    std::unique_ptr<Detail::Particles::ParticleParameter<Color>> ColorOverLifetime;

    std::unique_ptr<Detail::Particles::ParticleParameter<Radian<float>>> StartRotation;

    std::unique_ptr<Detail::Particles::ParticleParameter<Radian<float>>> RotationOverLifetime;

    std::unique_ptr<Detail::Particles::ParticleParameter<float>> StartSize;

    std::unique_ptr<Detail::Particles::ParticleParameter<float>> SizeOverLifetime;

    float StartDelay = 0.0f;

    float GravityModifier = 0.0f;

    bool Looping = true;

    // bool Prewarm = false;
};

} // namespace Pomdog
