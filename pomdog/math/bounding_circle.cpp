// Copyright (c) 2013-2021 mogemimi. Distributed under the MIT license.

#include "pomdog/math/bounding_circle.hpp"
#include "pomdog/math/bounding_box2d.hpp"
#include "pomdog/math/containment_type.hpp"
#include "pomdog/utility/assert.hpp"

namespace Pomdog {

BoundingCircle::BoundingCircle(const Vector2& center, float radius)
    : Center(center)
    , Radius(radius)
{
    POMDOG_ASSERT(radius >= 0);
}

ContainmentType BoundingCircle::Contains(const Vector2& point) const
{
    auto distanceSquared = Vector2::DistanceSquared(point, Center);
    auto radiusSquared = Radius * Radius;
    if (distanceSquared > radiusSquared) {
        return ContainmentType::Disjoint;
    }
    if (distanceSquared < radiusSquared) {
        return ContainmentType::Contains;
    }
    return ContainmentType::Intersects;
}

ContainmentType BoundingCircle::Contains(const BoundingBox2D& box) const
{
    bool inside = true;
    for (auto& corner : box.GetCorners()) {
        if (this->Contains(corner) == ContainmentType::Disjoint) {
            inside = false;
            break;
        }
    }
    if (inside) {
        return ContainmentType::Contains;
    }
    if (this->Intersects(box)) {
        return ContainmentType::Intersects;
    }
    return ContainmentType::Disjoint;
}

ContainmentType BoundingCircle::Contains(const BoundingCircle& circle) const
{
    auto distance = Vector2::Distance(this->Center, circle.Center);
    if (distance > this->Radius + circle.Radius) {
        return ContainmentType::Disjoint;
    }
    if (distance + circle.Radius < this->Radius) {
        return ContainmentType::Contains;
    }
    return ContainmentType::Intersects;
}

bool BoundingCircle::Intersects(const BoundingBox2D& box) const
{
    return box.Intersects(*this);
}

bool BoundingCircle::Intersects(const BoundingCircle& circle) const
{
    auto distance = Vector2::Distance(this->Center, circle.Center);
    return distance <= this->Radius + circle.Radius;
}

} // namespace Pomdog