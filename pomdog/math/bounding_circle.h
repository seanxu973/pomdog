// Copyright mogemimi. Distributed under the MIT license.

#pragma once

#include "pomdog/basic/export.h"
#include "pomdog/math/forward_declarations.h"
#include "pomdog/math/vector2.h"

namespace pomdog {

/// BoundingCircle is a bounding circle in 2D space.
class POMDOG_EXPORT BoundingCircle final {
public:
    Vector2 center;
    float radius;

public:
    BoundingCircle() noexcept = default;

    BoundingCircle(const Vector2& center, float radius);

    [[nodiscard]] ContainmentType
    Contains(const Vector2& box) const;

    [[nodiscard]] ContainmentType
    Contains(const BoundingBox2D& box) const;

    [[nodiscard]] ContainmentType
    Contains(const BoundingCircle& circle) const;

    [[nodiscard]] bool
    Intersects(const BoundingBox2D& box) const;

    [[nodiscard]] bool
    Intersects(const BoundingCircle& circle) const;
};

} // namespace pomdog
