// Copyright mogemimi. Distributed under the MIT license.

#pragma once

#include "pomdog/basic/conditional_compilation.h"
#include "pomdog/basic/export.h"
#include "pomdog/math/color.h"
#include "pomdog/math/matrix3x2.h"
#include "pomdog/math/matrix4x4.h"
#include "pomdog/math/radian.h"
#include "pomdog/math/rectangle.h"
#include "pomdog/math/vector2.h"
#include "pomdog/math/vector3.h"
#include "pomdog/math/vector4.h"

POMDOG_SUPPRESS_WARNINGS_GENERATED_BY_STD_HEADERS_BEGIN
#include <cstdint>
#include <functional>
#include <vector>
POMDOG_SUPPRESS_WARNINGS_GENERATED_BY_STD_HEADERS_END

namespace pomdog {

struct PrimitiveBatchVertex final {
    // {xyz} = position.xyz
    Vector3 Position;

    // {xyzw} = color.rgba
    Vector4 Color;
};

class POMDOG_EXPORT PolygonShapeBuilder final {
private:
    using Vertex = PrimitiveBatchVertex;
    std::vector<PrimitiveBatchVertex> vertices;
    std::size_t maxVertexCount;
    std::size_t minVertexCount;
    std::function<void()> onFlush;

public:
    PolygonShapeBuilder();

    explicit PolygonShapeBuilder(std::size_t maxVertexCount);

    void reset();

    [[nodiscard]] const PrimitiveBatchVertex*
    getData() const noexcept;

    [[nodiscard]] std::size_t
    getVertexCount() const noexcept;

    [[nodiscard]] bool
    isEmpty() const noexcept;

    [[nodiscard]] std::size_t
    getMaxVertexCount() const noexcept;

    void drawArc(
        const Vector2& position,
        float radius,
        const Radian<float>& startAngle,
        const Radian<float>& arcAngle,
        int segments,
        const Color& color);

    void drawBox(
        const Vector3& position,
        const Vector3& scale,
        const Color& color);

    void drawBox(
        const Vector3& position,
        const Vector3& scale,
        const Vector3& originPivot,
        const Color& color);

    void drawCircle(
        const Vector2& position,
        float radius,
        int segments,
        const Color& color);

    void drawCircle(
        const Vector3& position,
        float radius,
        int segments,
        const Color& color);

    // void drawEllipse();

    void drawLine(
        const Vector2& start,
        const Vector2& end,
        const Color& color,
        float weight);

    void drawLine(
        const Vector2& start,
        const Vector2& end,
        const Color& startColor,
        const Color& endColor,
        float weight);

    void drawPolyline(
        const std::vector<Vector2>& points,
        float thickness,
        const Color& color);

    // void drawPolygon(
    //    const std::vector<PrimitiveBatchVertex>& vertices,
    //    const Color& color);

    void drawRectangle(
        const Rectangle& sourceRect,
        const Color& color);

    void drawRectangle(
        const Rectangle& sourceRect,
        const Color& color1,
        const Color& color2,
        const Color& color3,
        const Color& color4);

    void drawRectangle(
        const Matrix3x2& matrix,
        const Vector2& position,
        float width,
        float height,
        const Color& color);

    ///@note
    /// Y
    /// ^   color4      color3
    /// |    +----------+
    /// |    |          |
    /// |    +----------+
    /// |   color1      color2
    /// |
    /// +-----------------> X
    ///
    void drawRectangle(
        const Matrix3x2& matrix,
        const Vector2& position,
        float width,
        float height,
        const Color& color1,
        const Color& color2,
        const Color& color3,
        const Color& color4);

    void drawRectangle(
        const Vector2& position,
        float width,
        float height,
        const Vector2& originPivot,
        const Color& color);

    void drawSphere(
        const Vector3& position,
        float radius,
        const Color& color,
        int segments);

    void drawTriangle(
        const Vector2& point1,
        const Vector2& point2,
        const Vector2& point3,
        const Color& color);

    void drawTriangle(
        const Vector2& point1,
        const Vector2& point2,
        const Vector2& point3,
        const Color& color1,
        const Color& color2,
        const Color& color3);

    void drawTriangle(
        const Vector3& point1,
        const Vector3& point2,
        const Vector3& point3,
        const Color& color1,
        const Color& color2,
        const Color& color3);

    void drawTriangle(
        const Vector3& point1,
        const Vector3& point2,
        const Vector3& point3,
        const Vector4& color1,
        const Vector4& color2,
        const Vector4& color3);
};

} // namespace pomdog
