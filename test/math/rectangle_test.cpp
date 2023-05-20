// Copyright mogemimi. Distributed under the MIT license.

#include "pomdog/math/point2d.h"
#include "pomdog/math/rectangle.h"
#include <catch_amalgamated.hpp>

using pomdog::Point2D;
using pomdog::Rectangle;

TEST_CASE("Rectangle", "[Rectangle]")
{
    SECTION("Rectangle")
    {
        using pomdog::Rectangle;
        Rectangle rect = {320, 240, 640, 480};
        REQUIRE(rect.x == 320);
        REQUIRE(rect.y == 240);
        REQUIRE(rect.width == 640);
        REQUIRE(rect.height == 480);
        REQUIRE(Point2D{320, 240} == rect.GetLocation());

        REQUIRE(rect.GetLeft() == 320);
        REQUIRE(320 + 640 == rect.GetRight());
        REQUIRE(rect.GetTop() == 240);
        REQUIRE(240 + 480 == rect.GetBottom());
    }
    SECTION("Location")
    {
        using pomdog::Rectangle;
        Rectangle rect = {320, 240, 640, 480};
        REQUIRE(rect.x == 320);
        REQUIRE(rect.y == 240);
        REQUIRE(rect.width == 640);
        REQUIRE(rect.height == 480);
        REQUIRE(Point2D{320, 240} == rect.GetLocation());

        rect.SetLocation(Point2D{-42, -24});
        REQUIRE(Point2D{-42, -24} == rect.GetLocation());
        REQUIRE(rect.x == -42);
        REQUIRE(rect.y == -24);
        REQUIRE(rect.width == 640);
        REQUIRE(rect.height == 480);
        REQUIRE(rect.GetLeft() == -42);
        REQUIRE(-42 + 640 == rect.GetRight());
        REQUIRE(rect.GetTop() == -24);
        REQUIRE(-24 + 480 == rect.GetBottom());
    }
    SECTION("Inflate")
    {
        using pomdog::Rectangle;
        Rectangle rect = {320, 240, 640, 480};
        rect.Inflate(96, 42);
        REQUIRE(rect.x == 320 - 96);
        REQUIRE(rect.y == 240 - 42);
        REQUIRE(rect.width == 640 + (96 * 2));
        REQUIRE(rect.height == 480 + (42 * 2));
        REQUIRE(320 - 96 == rect.GetLeft());
        REQUIRE(320 + 640 + 96 == rect.GetRight());
        REQUIRE(240 - 42 == rect.GetTop());
        REQUIRE(240 + 480 + 42 == rect.GetBottom());
    }
    SECTION("Offset")
    {
        using pomdog::Rectangle;
        Rectangle rect = {320, 240, 640, 480};
        rect.Offset(96, 42);
        REQUIRE(rect.x == 320 + 96);
        REQUIRE(rect.y == 240 + 42);
        REQUIRE(rect.width == 640);
        REQUIRE(rect.height == 480);
        REQUIRE(320 + 96 == rect.GetLeft());
        REQUIRE(320 + 96 + 640 == rect.GetRight());
        REQUIRE(240 + 42 == rect.GetTop());
        REQUIRE(240 + 42 + 480 == rect.GetBottom());
    }
    SECTION("Contains_Point2D")
    {
        using pomdog::Rectangle;
        Rectangle rect = {32, 24, 64, 48};
        const int left = rect.GetLeft();
        const int right = rect.GetRight();
        const int top = rect.GetTop();
        const int bottom = rect.GetBottom();
        const int centerX = rect.GetCenter().x;
        const int centerY = rect.GetCenter().y;

        REQUIRE(rect.Contains(left, top));
        REQUIRE(rect.Contains(centerX, centerY));
        REQUIRE_FALSE(rect.Contains(left - 1, centerY));

        REQUIRE(rect.Contains({left, top}));
        REQUIRE(rect.Contains({left, centerY}));
        REQUIRE(rect.Contains({left, bottom}));
        REQUIRE(rect.Contains({right, top}));
        REQUIRE(rect.Contains({right, centerY}));
        REQUIRE(rect.Contains({right, bottom}));
        REQUIRE(rect.Contains({left, top}));
        REQUIRE(rect.Contains({centerX, top}));
        REQUIRE(rect.Contains({right, top}));
        REQUIRE(rect.Contains({left, bottom}));
        REQUIRE(rect.Contains({centerX, bottom}));
        REQUIRE(rect.Contains({right, bottom}));

        REQUIRE(rect.Contains({centerX, centerY}));
        REQUIRE(rect.Contains({left + 1, top + 1}));
        REQUIRE(rect.Contains({left + 1, bottom - 1}));
        REQUIRE(rect.Contains({right - 1, top + 1}));
        REQUIRE(rect.Contains({right - 1, bottom - 1}));

        REQUIRE_FALSE(rect.Contains({left - 1, centerY}));
        REQUIRE_FALSE(rect.Contains({right + 1, centerY}));
        REQUIRE_FALSE(rect.Contains({centerX, top - 1}));
        REQUIRE_FALSE(rect.Contains({centerX, bottom + 1}));
    }
    SECTION("Intersects_Point2D")
    {
        using pomdog::Rectangle;
        Rectangle rect = {32, 24, 64, 48};
        const int left = rect.GetLeft();
        const int right = rect.GetRight();
        const int top = rect.GetTop();
        const int bottom = rect.GetBottom();
        const int centerX = rect.GetCenter().x;
        const int centerY = rect.GetCenter().y;

        REQUIRE(rect.Contains({left, top}));
        REQUIRE(rect.Contains({left, centerY}));
        REQUIRE(rect.Contains({left, bottom}));
        REQUIRE(rect.Contains({right, top}));
        REQUIRE(rect.Contains({right, centerY}));
        REQUIRE(rect.Contains({right, bottom}));
        REQUIRE(rect.Contains({left, top}));
        REQUIRE(rect.Contains({centerX, top}));
        REQUIRE(rect.Contains({right, top}));
        REQUIRE(rect.Contains({left, bottom}));
        REQUIRE(rect.Contains({centerX, bottom}));
        REQUIRE(rect.Contains({right, bottom}));

        REQUIRE(rect.Contains({centerX, centerY}));
        REQUIRE(rect.Contains({left + 1, top + 1}));
        REQUIRE(rect.Contains({left + 1, bottom - 1}));
        REQUIRE(rect.Contains({right - 1, top + 1}));
        REQUIRE(rect.Contains({right - 1, bottom - 1}));

        REQUIRE_FALSE(rect.Contains({left - 1, centerY}));
        REQUIRE_FALSE(rect.Contains({right + 1, centerY}));
        REQUIRE_FALSE(rect.Contains({centerX, top - 1}));
        REQUIRE_FALSE(rect.Contains({centerX, bottom + 1}));
    }
    SECTION("Contains_Rectangle")
    {
        using pomdog::Rectangle;
        Rectangle rect = {32, 24, 64, 48};

        REQUIRE(rect.Contains(rect));
        REQUIRE(rect.Contains({32, 24, 64, 48}));
        REQUIRE_FALSE(rect.Contains({32 - 1, 24, 64, 48}));
        REQUIRE_FALSE(rect.Contains({32, 24 - 1, 64, 48}));
        REQUIRE_FALSE(rect.Contains({32, 24, 64 + 1, 48}));
        REQUIRE_FALSE(rect.Contains({32, 24, 64, 48 + 1}));
    }
    SECTION("Intersects_Rectangle")
    {
        using pomdog::Rectangle;
        Rectangle rect = {32, 24, 64, 48};

        REQUIRE(rect.Intersects({32, 24, 64, 48}));
        REQUIRE(rect.Intersects({32 - 1, 24, 64, 48}));
        REQUIRE(rect.Intersects({32, 24 - 1, 64, 48}));
        REQUIRE(rect.Intersects({32, 24, 64 + 1, 48}));
        REQUIRE(rect.Intersects({32, 24, 64, 48 + 1}));
    }
}
