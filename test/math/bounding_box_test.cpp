// Copyright mogemimi. Distributed under the MIT license.

#include "pomdog/math/bounding_box.h"
#include "pomdog/math/bounding_sphere.h"
#include "pomdog/math/containment_type.h"
#include <catch_amalgamated.hpp>

using namespace pomdog;

TEST_CASE("BoundingBox", "[BoundingBox]")
{
    BoundingBox box;

    SECTION("CornerCount")
    {
        STATIC_REQUIRE(BoundingBox::CornerCount == 8);
    }
    SECTION("Constructors")
    {
        BoundingBox box2;
        box2.min = Vector3::Zero();
        box2.max = Vector3::UnitY();

        box = box2;
        REQUIRE(Vector3::Zero() == box.min);
        REQUIRE(Vector3::UnitY() == box.max);

        BoundingBox box3{Vector3::UnitX(), Vector3::UnitZ()};
        box = box3;
        REQUIRE(Vector3::UnitX() == box.min);
        REQUIRE(Vector3::UnitX() == box3.min);
        REQUIRE(Vector3::UnitZ() == box.max);
        REQUIRE(Vector3::UnitZ() == box3.max);
    }
    SECTION("GetCorners")
    {
        box.min = Vector3{12.0f, 13.0f, 14.0f};
        box.max = Vector3{15.0f, 16.0f, 17.0f};

        auto corners = box.GetCorners();
        REQUIRE_FALSE(corners.empty());
        REQUIRE(BoundingBox::CornerCount == corners.size());
        REQUIRE(Vector3{12.0f, 13.0f, 14.0f} == box.min);
        REQUIRE(Vector3{15.0f, 16.0f, 17.0f} == box.max);
        REQUIRE(corners[0] == Vector3(box.min.x, box.max.y, box.max.z));
        REQUIRE(corners[1] == Vector3(box.max.x, box.max.y, box.max.z));
        REQUIRE(corners[2] == Vector3(box.max.x, box.min.y, box.max.z));
        REQUIRE(corners[3] == Vector3(box.min.x, box.min.y, box.max.z));
        REQUIRE(corners[4] == Vector3(box.min.x, box.max.y, box.min.z));
        REQUIRE(corners[5] == Vector3(box.max.x, box.max.y, box.min.z));
        REQUIRE(corners[6] == Vector3(box.max.x, box.min.y, box.min.z));
        REQUIRE(corners[7] == Vector3(box.min.x, box.min.y, box.min.z));
    }
    SECTION("Contains_Vector3")
    {
        constexpr auto a = 12.0f;
        constexpr auto b = 16.0f;
        constexpr auto c = 24.0f;
        constexpr auto d = 32.0f;
        constexpr auto e = 64.0f;
        constexpr auto f = 96.0f;

        box.min = Vector3{a, b, c};
        box.max = Vector3{d, e, f};

        REQUIRE(ContainmentType::Contains == box.Contains(Vector3(a + 1, b + 1, c + 1)));
        REQUIRE(ContainmentType::Contains == box.Contains(Vector3(d - 1, b + 1, c + 1)));
        REQUIRE(ContainmentType::Contains == box.Contains(Vector3(a + 1, e - 1, c + 1)));
        REQUIRE(ContainmentType::Contains == box.Contains(Vector3(d - 1, e - 1, c + 1)));
        REQUIRE(ContainmentType::Contains == box.Contains(Vector3(a + 1, b + 1, f - 1)));
        REQUIRE(ContainmentType::Contains == box.Contains(Vector3(d - 1, b + 1, f - 1)));
        REQUIRE(ContainmentType::Contains == box.Contains(Vector3(a + 1, e - 1, f - 1)));
        REQUIRE(ContainmentType::Contains == box.Contains(Vector3(d - 1, e - 1, f - 1)));

        REQUIRE(ContainmentType::Intersects == box.Contains(Vector3(a, b, c)));
        REQUIRE(ContainmentType::Intersects == box.Contains(Vector3(d, b, c)));
        REQUIRE(ContainmentType::Intersects == box.Contains(Vector3(a, e, c)));
        REQUIRE(ContainmentType::Intersects == box.Contains(Vector3(d, e, c)));
        REQUIRE(ContainmentType::Intersects == box.Contains(Vector3(a, b, f)));
        REQUIRE(ContainmentType::Intersects == box.Contains(Vector3(d, b, f)));
        REQUIRE(ContainmentType::Intersects == box.Contains(Vector3(a, e, f)));
        REQUIRE(ContainmentType::Intersects == box.Contains(Vector3(d, e, f)));

        REQUIRE(ContainmentType::Intersects == box.Contains(Vector3((d + a) / 2, b, c)));
        REQUIRE(ContainmentType::Intersects == box.Contains(Vector3((d + a) / 2, b, f)));
        REQUIRE(ContainmentType::Intersects == box.Contains(Vector3((d + a) / 2, e, c)));
        REQUIRE(ContainmentType::Intersects == box.Contains(Vector3((d + a) / 2, e, f)));
        REQUIRE(ContainmentType::Intersects == box.Contains(Vector3(a, (e + b) / 2, c)));
        REQUIRE(ContainmentType::Intersects == box.Contains(Vector3(a, (e + b) / 2, f)));
        REQUIRE(ContainmentType::Intersects == box.Contains(Vector3(d, (e + b) / 2, c)));
        REQUIRE(ContainmentType::Intersects == box.Contains(Vector3(d, (e + b) / 2, f)));
        REQUIRE(ContainmentType::Intersects == box.Contains(Vector3(a, b, (f + c) / 2)));
        REQUIRE(ContainmentType::Intersects == box.Contains(Vector3(a, e, (f + c) / 2)));
        REQUIRE(ContainmentType::Intersects == box.Contains(Vector3(d, b, (f + c) / 2)));
        REQUIRE(ContainmentType::Intersects == box.Contains(Vector3(d, e, (f + c) / 2)));

        REQUIRE(ContainmentType::Disjoint == box.Contains(Vector3(a - 1, b, c)));
        REQUIRE(ContainmentType::Disjoint == box.Contains(Vector3(d + 1, b, c)));
        REQUIRE(ContainmentType::Disjoint == box.Contains(Vector3(a, b - 1, c)));
        REQUIRE(ContainmentType::Disjoint == box.Contains(Vector3(d, e + 1, c)));
        REQUIRE(ContainmentType::Disjoint == box.Contains(Vector3(a, b, c - 1)));
        REQUIRE(ContainmentType::Disjoint == box.Contains(Vector3(d, b, f + 1)));

        REQUIRE(ContainmentType::Disjoint == box.Contains(Vector3(a - 1, b - 1, c)));
        REQUIRE(ContainmentType::Disjoint == box.Contains(Vector3(d + 1, e + 1, c)));
        REQUIRE(ContainmentType::Disjoint == box.Contains(Vector3(a - 1, e + 1, c)));
        REQUIRE(ContainmentType::Disjoint == box.Contains(Vector3(d + 1, b - 1, c)));

        REQUIRE(ContainmentType::Disjoint == box.Contains(Vector3(a - 1, b - 1, c - 1)));
        REQUIRE(ContainmentType::Disjoint == box.Contains(Vector3(d + 1, e + 1, c - 1)));
        REQUIRE(ContainmentType::Disjoint == box.Contains(Vector3(a - 1, e + 1, c - 1)));
        REQUIRE(ContainmentType::Disjoint == box.Contains(Vector3(d + 1, b - 1, c - 1)));
        REQUIRE(ContainmentType::Disjoint == box.Contains(Vector3(a - 1, b - 1, f + 1)));
        REQUIRE(ContainmentType::Disjoint == box.Contains(Vector3(d + 1, e + 1, f + 1)));
        REQUIRE(ContainmentType::Disjoint == box.Contains(Vector3(a - 1, e + 1, f + 1)));
        REQUIRE(ContainmentType::Disjoint == box.Contains(Vector3(d + 1, b - 1, f + 1)));
    }
    SECTION("Contains_BoundingBox")
    {
        constexpr auto a = 12.0f;
        constexpr auto b = 16.0f;
        constexpr auto c = 24.0f;
        constexpr auto d = 32.0f;
        constexpr auto e = 64.0f;
        constexpr auto f = 96.0f;

        box.min = Vector3{a, b, c};
        box.max = Vector3{d, e, f};

        REQUIRE(ContainmentType::Contains == box.Contains(box));

        using pomdog::math::Lerp;
        REQUIRE(ContainmentType::Contains == box.Contains(BoundingBox{box.min, Lerp(box.min, box.max, 0.01f)}));
        REQUIRE(ContainmentType::Contains == box.Contains(BoundingBox{box.min, Lerp(box.min, box.max, 0.5f)}));
        REQUIRE(ContainmentType::Contains == box.Contains(BoundingBox{box.min, Lerp(box.min, box.max, 0.99f)}));
        REQUIRE(ContainmentType::Intersects == box.Contains(BoundingBox{box.min, Lerp(box.min, box.max, 1.1f)}));
        REQUIRE(ContainmentType::Intersects == box.Contains(BoundingBox{Vector3::Zero(), Vector3(a, b, c)}));
        REQUIRE(ContainmentType::Disjoint == box.Contains(BoundingBox{Vector3::Zero(), Vector3(a - 1, b, c)}));
    }
    SECTION("Contains_BoundingSphere")
    {
        using pomdog::math::Lerp;
        box.min = Vector3{12.0f, 16.0f, 24.0f};
        box.max = Vector3{32.0f, 64.0f, 96.0f};
        const auto center = Lerp(box.min, box.max, 0.5f);

        REQUIRE(ContainmentType::Contains == box.Contains(BoundingSphere{center, 1.0f}));
        REQUIRE(ContainmentType::Contains == box.Contains(BoundingSphere{center, (box.max - box.min).x / 2}));
        REQUIRE(ContainmentType::Intersects == box.Contains(BoundingSphere{center, (box.max - box.min).y / 2}));
        REQUIRE(ContainmentType::Intersects == box.Contains(BoundingSphere{center, (box.max - box.min).z / 2}));

        REQUIRE(ContainmentType::Intersects == box.Contains(BoundingSphere{Vector3{0.0f, 16.0f, 24.0f}, 12.01f}));
        REQUIRE(ContainmentType::Intersects == box.Contains(BoundingSphere{Vector3{12.0f, 0.0f, 24.0f}, 16.01f}));
        REQUIRE(ContainmentType::Intersects == box.Contains(BoundingSphere{Vector3{12.0f, 16.0f, 0.0f}, 24.01f}));
        REQUIRE(ContainmentType::Disjoint == box.Contains(BoundingSphere{Vector3{0.0f, 16.0f, 24.0f}, 11.99f}));
        REQUIRE(ContainmentType::Disjoint == box.Contains(BoundingSphere{Vector3{12.0f, 0.0f, 24.0f}, 15.99f}));
        REQUIRE(ContainmentType::Disjoint == box.Contains(BoundingSphere{Vector3{12.0f, 16.0f, 0.0f}, 23.99f}));
    }
    SECTION("Intersects_BoundingBox")
    {
        constexpr auto a = 12.0f;
        constexpr auto b = 16.0f;
        constexpr auto c = 24.0f;
        constexpr auto d = 32.0f;
        constexpr auto e = 64.0f;
        constexpr auto f = 96.0f;

        box.min = Vector3{a, b, c};
        box.max = Vector3{d, e, f};

        REQUIRE(box.Intersects(box));
        REQUIRE(box.Intersects(BoundingBox{box.min, math::Lerp(box.min, box.max, 0.01f)}));
        REQUIRE(box.Intersects(BoundingBox{box.min, math::Lerp(box.min, box.max, 0.5f)}));
        REQUIRE(box.Intersects(BoundingBox{box.min, math::Lerp(box.min, box.max, 0.99f)}));
        REQUIRE(box.Intersects(BoundingBox{box.min, math::Lerp(box.min, box.max, 1.1f)}));
        REQUIRE(box.Intersects(BoundingBox{Vector3::Zero(), Vector3(a, b, c)}));
        REQUIRE_FALSE(box.Intersects(BoundingBox{Vector3::Zero(), Vector3(a - 1, b, c)}));
    }
    SECTION("Intersects_BoundingSphere")
    {
        box.min = Vector3{12.0f, 16.0f, 24.0f};
        box.max = Vector3{32.0f, 64.0f, 96.0f};
        const auto center = math::Lerp(box.min, box.max, 0.5f);

        REQUIRE(box.Intersects(BoundingSphere{center, 1.0f}));
        REQUIRE(box.Intersects(BoundingSphere{center, (box.max - box.min).x / 2}));
        REQUIRE(box.Intersects(BoundingSphere{center, (box.max - box.min).y / 2}));
        REQUIRE(box.Intersects(BoundingSphere{center, (box.max - box.min).z / 2}));

        REQUIRE(box.Intersects(BoundingSphere{Vector3{0.0f, 16.0f, 24.0f}, 12.01f}));
        REQUIRE(box.Intersects(BoundingSphere{Vector3{12.0f, 0.0f, 24.0f}, 16.01f}));
        REQUIRE(box.Intersects(BoundingSphere{Vector3{12.0f, 16.0f, 0.0f}, 24.01f}));
        REQUIRE_FALSE(box.Intersects(BoundingSphere{Vector3{0.0f, 16.0f, 24.0f}, 11.99f}));
        REQUIRE_FALSE(box.Intersects(BoundingSphere{Vector3{12.0f, 0.0f, 24.0f}, 15.99f}));
        REQUIRE_FALSE(box.Intersects(BoundingSphere{Vector3{12.0f, 16.0f, 0.0f}, 23.99f}));
    }
}
