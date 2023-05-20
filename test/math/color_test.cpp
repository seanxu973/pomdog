// Copyright mogemimi. Distributed under the MIT license.

#include "pomdog/math/color.h"
#include "pomdog/math/vector3.h"
#include "pomdog/math/vector4.h"
#include <catch_amalgamated.hpp>

using namespace pomdog;
using pomdog::Color;
using pomdog::Vector3;
using pomdog::Vector4;

TEST_CASE("Color", "[Color]")
{
    SECTION("FirstTestCase")
    {
        Color color{255, 255, 255, 255};
        REQUIRE(color.r == 255);
        REQUIRE(color.g == 255);
        REQUIRE(color.b == 255);
        REQUIRE(color.a == 255);

        color = pomdog::Color{0, 0, 0, 0};
        REQUIRE(color.r == 0);
        REQUIRE(color.g == 0);
        REQUIRE(color.b == 0);
        REQUIRE(color.a == 0);

        color = pomdog::Color{1, 2, 3, 4};
        REQUIRE(color.r == 1);
        REQUIRE(color.g == 2);
        REQUIRE(color.b == 3);
        REQUIRE(color.a == 4);
    }
    SECTION("Constants")
    {
        REQUIRE(Color::Black() == Color{0, 0, 0, 255});
        REQUIRE(Color::White() == Color{255, 255, 255, 255});
        REQUIRE(Color::Red() == Color{255, 0, 0, 255});
        REQUIRE(Color::Green() == Color{0, 255, 0, 255});
        REQUIRE(Color::Blue() == Color{0, 0, 255, 255});
        REQUIRE(Color::Yellow() == Color{255, 255, 0, 255});
        REQUIRE(Color::TransparentBlack() == Color{0, 0, 0, 0});
        REQUIRE(Color::CornflowerBlue() == Color{100, 149, 237, 255});
    }
    SECTION("ToVector")
    {
        Color color{255, 255, 255, 255};
        REQUIRE(Vector3{1.0f, 1.0f, 1.0f} == color.ToVector3());
        REQUIRE(Vector4{1.0f, 1.0f, 1.0f, 1.0f} == color.ToVector4());

        color = Color{0, 0, 0, 0};
        REQUIRE(Vector3{0.0f, 0.0f, 0.0f} == color.ToVector3());
        REQUIRE(Vector4{0.0f, 0.0f, 0.0f, 0.0f} == color.ToVector4());

        color = Color{12, 34, 56, 78};
        REQUIRE(std::abs(12.0f / 255.0f - color.ToVector3().x) < std::numeric_limits<float>::epsilon());
        REQUIRE(std::abs(34.0f / 255.0f - color.ToVector3().y) < std::numeric_limits<float>::epsilon());
        REQUIRE(std::abs(56.0f / 255.0f - color.ToVector3().z) < std::numeric_limits<float>::epsilon());
        REQUIRE(std::abs(12.0f / 255.0f - color.ToVector4().x) < std::numeric_limits<float>::epsilon());
        REQUIRE(std::abs(34.0f / 255.0f - color.ToVector4().y) < std::numeric_limits<float>::epsilon());
        REQUIRE(std::abs(56.0f / 255.0f - color.ToVector4().z) < std::numeric_limits<float>::epsilon());
        REQUIRE(std::abs(78.0f / 255.0f - color.ToVector4().w) < std::numeric_limits<float>::epsilon());
    }
    SECTION("FromVector")
    {
        REQUIRE(Color{0, 0, 0, 255} == Color(Vector3{0.0f, 0.0f, 0.0f}));
        REQUIRE(Color{255, 255, 255, 255} == Color(Vector3{1.0f, 1.0f, 1.0f}));

        REQUIRE(Color{0, 0, 0, 0} == Color(Vector4{0.0f, 0.0f, 0.0f, 0.0f}));
        REQUIRE(Color{255, 255, 255, 255} == Color(Vector4{1.0f, 1.0f, 1.0f, 1.0f}));

        REQUIRE(Color{255, 0, 0, 255} == Color(Vector3{1.0f, 0.0f, 0.0f}));
        REQUIRE(Color{0, 255, 0, 255} == Color(Vector3{0.0f, 1.0f, 0.0f}));
        REQUIRE(Color{0, 0, 255, 255} == Color(Vector3{0.0f, 0.0f, 1.0f}));

        REQUIRE(Color{255, 0, 0, 0} == Color(Vector4{1.0f, 0.0f, 0.0f, 0.0f}));
        REQUIRE(Color{0, 255, 0, 0} == Color(Vector4{0.0f, 1.0f, 0.0f, 0.0f}));
        REQUIRE(Color{0, 0, 255, 0} == Color(Vector4{0.0f, 0.0f, 1.0f, 0.0f}));
        REQUIRE(Color{0, 0, 0, 255} == Color(Vector4{0.0f, 0.0f, 0.0f, 1.0f}));

        REQUIRE(std::abs(0.3f * 255 - Color(Vector3{0.3f, 0.4f, 0.5f}).r) <= 0.5f);
        REQUIRE(std::abs(0.4f * 255 - Color(Vector3{0.3f, 0.4f, 0.5f}).g) <= 0.5f);
        REQUIRE(std::abs(0.5f * 255 - Color(Vector3{0.3f, 0.4f, 0.5f}).b) <= 0.5f);

        REQUIRE(std::abs(0.3f * 255 - Color(Vector4{0.3f, 0.4f, 0.5f, 0.6f}).r) <= 0.5f);
        REQUIRE(std::abs(0.4f * 255 - Color(Vector4{0.3f, 0.4f, 0.5f, 0.6f}).g) <= 0.5f);
        REQUIRE(std::abs(0.5f * 255 - Color(Vector4{0.3f, 0.4f, 0.5f, 0.6f}).b) <= 0.5f);
        REQUIRE(std::abs(0.6f * 255 - Color(Vector4{0.3f, 0.4f, 0.5f, 0.6f}).a) <= 0.5f);
    }
    SECTION("FromPackedValue")
    {
        REQUIRE(Color{0, 0, 0, 0} == Color::FromPackedValue(0x00000000));
        REQUIRE(Color{255, 255, 255, 255} == Color::FromPackedValue(0xffffffff));
        REQUIRE(Color{204, 221, 238, 255} == Color::FromPackedValue(0xccddeeff));
        REQUIRE(Color{100, 149, 237, 255} == Color::FromPackedValue(0x6495edff));
        REQUIRE(Color{100, 149, 237, 153} == Color::FromPackedValue(0x6495ed99));
    }
    SECTION("Multiply")
    {
        REQUIRE(Color{255, 255, 255, 255} == math::Multiply(Color::White(), 2.0f));
        REQUIRE(Color{255, 255, 255, 255} == math::Multiply(Color::White(), 1.0f));
        REQUIRE(Color{128, 128, 128, 128} == math::Multiply(Color::White(), 0.5f));
        REQUIRE(Color{64, 64, 64, 64} == math::Multiply(Color::White(), 0.25f));
        REQUIRE(Color{0, 0, 0, 0} == math::Multiply(Color::White(), 0.0f));
        REQUIRE(Color{0, 0, 0, 0} == math::Multiply(Color::TransparentBlack(), 2.0f));
        REQUIRE(Color{0, 0, 0, 0} == math::Multiply(Color::TransparentBlack(), 1.0f));
        REQUIRE(Color{0, 0, 0, 0} == math::Multiply(Color::TransparentBlack(), 0.0f));
    }
}
