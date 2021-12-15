// Copyright mogemimi. Distributed under the MIT license.

#include "pomdog/experimental/particles/emitter_shapes/particle_emitter_shape_sphere.hpp"
#include "pomdog/basic/conditional_compilation.hpp"
#include "pomdog/experimental/random/xoroshiro128_star_star.hpp"
#include "pomdog/utility/assert.hpp"

POMDOG_SUPPRESS_WARNINGS_GENERATED_BY_STD_HEADERS_BEGIN
#include <random>
POMDOG_SUPPRESS_WARNINGS_GENERATED_BY_STD_HEADERS_END

namespace pomdog::detail::particles {

ParticleEmitterShapeSphere::ParticleEmitterShapeSphere(float radiusIn)
    : radius(radiusIn)
{
}

std::tuple<Vector3, Vector3>
ParticleEmitterShapeSphere::Compute(random::Xoroshiro128StarStar& random) const
{
    POMDOG_ASSERT(radius >= 0.0f);
    std::uniform_real_distribution<float> dist(-radius, radius);

    auto emitPosition = Vector3{dist(random), dist(random), dist(random)};
    auto emitDirection = math::Normalize(emitPosition);
    return std::make_tuple(std::move(emitPosition), std::move(emitDirection));
}

} // namespace pomdog::detail::particles
