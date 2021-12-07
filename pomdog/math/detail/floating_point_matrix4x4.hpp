// Copyright (c) 2013-2021 mogemimi. Distributed under the MIT license.

#pragma once

#include "pomdog/basic/conditional_compilation.hpp"
#include "pomdog/basic/export.hpp"
#include "pomdog/math/forward_declarations.hpp"

POMDOG_SUPPRESS_WARNINGS_GENERATED_BY_STD_HEADERS_BEGIN
#include <cstddef>
#include <cstdint>
#include <type_traits>
POMDOG_SUPPRESS_WARNINGS_GENERATED_BY_STD_HEADERS_END

namespace Pomdog::Detail {

/// FloatingPointMatrix4x4 is a 4x4 matrix in row-major order.
template <typename T>
class POMDOG_EXPORT FloatingPointMatrix4x4 final {
public:
    static_assert(std::is_floating_point<T>::value, "T is floating point.");
    using value_type = T;

    T m[4][4];

private:
    static constexpr std::size_t RowSize = 4;
    static constexpr std::size_t ColumnSize = 4;

public:
    // Constructors:
    FloatingPointMatrix4x4() noexcept = default;

    /// Constructs from floating-point values.
    FloatingPointMatrix4x4(
        T m00, T m01, T m02, T m03,
        T m10, T m11, T m12, T m13,
        T m20, T m21, T m22, T m23,
        T m30, T m31, T m32, T m33) noexcept;

    // Assignment operators:
    FloatingPointMatrix4x4& operator*=(const FloatingPointMatrix4x4&) noexcept;
    FloatingPointMatrix4x4& operator+=(const FloatingPointMatrix4x4&) noexcept;
    FloatingPointMatrix4x4& operator-=(const FloatingPointMatrix4x4&) noexcept;
    FloatingPointMatrix4x4& operator*=(T scaleFactor) noexcept;
    FloatingPointMatrix4x4& operator/=(T scaleFactor);

    // Unary operators:
    FloatingPointMatrix4x4 operator+() const noexcept;
    FloatingPointMatrix4x4 operator-() const noexcept;

    // Binary operators:
    [[nodiscard]] FloatingPointMatrix4x4 operator+(const FloatingPointMatrix4x4&) const noexcept;
    [[nodiscard]] FloatingPointMatrix4x4 operator-(const FloatingPointMatrix4x4&) const noexcept;
    [[nodiscard]] FloatingPointMatrix4x4 operator*(const FloatingPointMatrix4x4&) const noexcept;
    [[nodiscard]] FloatingPointMatrix4x4 operator*(T scaleFactor) const noexcept;
    [[nodiscard]] FloatingPointMatrix4x4 operator/(T scaleFactor) const;

    [[nodiscard]] bool operator==(const FloatingPointMatrix4x4&) const noexcept;
    [[nodiscard]] bool operator!=(const FloatingPointMatrix4x4&) const noexcept;

    // Function-call operators:
    [[nodiscard]] const T& operator()(std::size_t row, std::size_t column) const;
    [[nodiscard]] T& operator()(std::size_t row, std::size_t column);

    void SetTranslation(const FloatingPointVector3<T>&) noexcept;

    [[nodiscard]] FloatingPointVector3<T>
    GetTranslation() const noexcept;

    void SetScale(const FloatingPointVector3<T>&) noexcept;

    [[nodiscard]] FloatingPointVector3<T>
    GetScale() const noexcept;

    [[nodiscard]] T Determinant() const noexcept;

    [[nodiscard]] FloatingPointMatrix3x3<T>
    Minor3x3(std::size_t row, std::size_t column) const;

    [[nodiscard]] static FloatingPointMatrix4x4
    Multiply(const FloatingPointMatrix4x4& matrix1, const FloatingPointMatrix4x4& matrix2) noexcept;

    [[nodiscard]] static FloatingPointMatrix4x4
    Multiply(const FloatingPointMatrix4x4& matrix1, T scaleFactor) noexcept;

    [[nodiscard]] static FloatingPointMatrix4x4
    Adjoint(const FloatingPointMatrix4x4& matrix);

    static void
    Transpose(const FloatingPointMatrix4x4& matrix, FloatingPointMatrix4x4& result) noexcept;

    [[nodiscard]] static FloatingPointMatrix4x4
    Transpose(const FloatingPointMatrix4x4& matrix) noexcept;

    static void
    Invert(const FloatingPointMatrix4x4& matrix, FloatingPointMatrix4x4& result);

    [[nodiscard]] static FloatingPointMatrix4x4
    Invert(const FloatingPointMatrix4x4& matrix);

    static void
    Lerp(const FloatingPointMatrix4x4& source1, const FloatingPointMatrix4x4& source2, T amount,
        FloatingPointMatrix4x4& result) noexcept;

    [[nodiscard]] static FloatingPointMatrix4x4
    Lerp(const FloatingPointMatrix4x4& source1, const FloatingPointMatrix4x4& source2, T amount) noexcept;

    static void
    CreateTranslation(const FloatingPointVector3<T>& position, FloatingPointMatrix4x4& result) noexcept;

    [[nodiscard]] static FloatingPointMatrix4x4
    CreateTranslation(const FloatingPointVector3<T>& position) noexcept;

    static void
    CreateScale(T scale, FloatingPointMatrix4x4& result) noexcept;

    [[nodiscard]] static FloatingPointMatrix4x4
    CreateScale(T scale) noexcept;

    static void
    CreateScale(const FloatingPointVector3<T>& scale, FloatingPointMatrix4x4& result) noexcept;

    [[nodiscard]] static FloatingPointMatrix4x4
    CreateScale(const FloatingPointVector3<T>& scale) noexcept;

    static void
    CreateRotationX(const Radian<T>& angle, FloatingPointMatrix4x4& result);

    [[nodiscard]] static FloatingPointMatrix4x4
    CreateRotationX(const Radian<T>& angle);

    static void
    CreateRotationY(const Radian<T>& angle, FloatingPointMatrix4x4& result);

    [[nodiscard]] static FloatingPointMatrix4x4
    CreateRotationY(const Radian<T>& angle);

    static void
    CreateRotationZ(const Radian<T>& angle, FloatingPointMatrix4x4& result);

    [[nodiscard]] static FloatingPointMatrix4x4
    CreateRotationZ(const Radian<T>& angle);

    static void
    CreateFromQuaternion(const FloatingPointQuaternion<T>& quaternion, FloatingPointMatrix4x4& result);

    [[nodiscard]] static FloatingPointMatrix4x4
    CreateFromQuaternion(const FloatingPointQuaternion<T>& quaternion);

    static void
    CreateLookAtLH(const FloatingPointVector3<T>& eye, const FloatingPointVector3<T>& at,
        const FloatingPointVector3<T>& up, FloatingPointMatrix4x4& result);

    [[nodiscard]] static FloatingPointMatrix4x4
    CreateLookAtLH(const FloatingPointVector3<T>& eye, const FloatingPointVector3<T>& at,
        const FloatingPointVector3<T>& up);

    static void
    CreateLookAtRH(const FloatingPointVector3<T>& eye, const FloatingPointVector3<T>& at,
        const FloatingPointVector3<T>& up, FloatingPointMatrix4x4& result);

    [[nodiscard]] static FloatingPointMatrix4x4
    CreateLookAtRH(const FloatingPointVector3<T>& eye, const FloatingPointVector3<T>& at,
        const FloatingPointVector3<T>& up);

    static void
    CreatePerspectiveLH(T width, T height, T zNear, T zFar, FloatingPointMatrix4x4& result);

    [[nodiscard]] static FloatingPointMatrix4x4
    CreatePerspectiveLH(T width, T height, T zNear, T zFar);

    static void
    CreatePerspectiveRH(T width, T height, T zNear, T zFar, FloatingPointMatrix4x4& result);

    [[nodiscard]] static FloatingPointMatrix4x4
    CreatePerspectiveRH(T width, T height, T zNear, T zFar);

    static void
    CreatePerspectiveFieldOfViewLH(const Radian<T>& fovy, T aspect, T zNear, T zFar,
        FloatingPointMatrix4x4& result);

    [[nodiscard]] static FloatingPointMatrix4x4
    CreatePerspectiveFieldOfViewLH(const Radian<T>& fovy, T aspect, T zNear, T zFar);

    static void
    CreatePerspectiveFieldOfViewRH(const Radian<T>& fovy, T aspect, T zNear, T zFar,
        FloatingPointMatrix4x4& result);

    [[nodiscard]] static FloatingPointMatrix4x4
    CreatePerspectiveFieldOfViewRH(const Radian<T>& fovy, T aspect, T zNear, T zFar);

    static void
    CreatePerspectiveOffCenterLH(T left, T right, T bottom, T top, T zNear, T zFar,
        FloatingPointMatrix4x4& result);

    [[nodiscard]] static FloatingPointMatrix4x4
    CreatePerspectiveOffCenterLH(T left, T right, T bottom, T top, T zNear, T zFar);

    static void
    CreatePerspectiveOffCenterRH(T left, T right, T bottom, T top, T zNear, T zFar,
        FloatingPointMatrix4x4& result);

    [[nodiscard]] static FloatingPointMatrix4x4
    CreatePerspectiveOffCenterRH(T left, T right, T bottom, T top, T zNear, T zFar);

    static void
    CreateOrthographicLH(T width, T height, T zNearPlane, T zFarPlane,
        FloatingPointMatrix4x4& result);

    [[nodiscard]] static FloatingPointMatrix4x4
    CreateOrthographicLH(T width, T height, T zNearPlane, T zFarPlane);

    static void
    CreateOrthographicRH(T width, T height, T zNearPlane, T zFarPlane,
        FloatingPointMatrix4x4& result);

    [[nodiscard]] static FloatingPointMatrix4x4
    CreateOrthographicRH(T width, T height, T zNearPlane, T zFarPlane);

    static void
    CreateOrthographicOffCenterLH(T left, T right, T bottom, T top, T zNearPlane, T zFarPlane,
        FloatingPointMatrix4x4& result);

    [[nodiscard]] static FloatingPointMatrix4x4
    CreateOrthographicOffCenterLH(T left, T right, T bottom, T top, T zNearPlane, T zFarPlane);

    static void
    CreateOrthographicOffCenterRH(T left, T right, T bottom, T top, T zNearPlane, T zFarPlane,
        FloatingPointMatrix4x4& result);

    [[nodiscard]] static FloatingPointMatrix4x4
    CreateOrthographicOffCenterRH(T left, T right, T bottom, T top, T zNearPlane, T zFarPlane);

    static void
    CreateFromAxisAngle(const FloatingPointVector3<T>& axis, const Radian<T>& angle, FloatingPointMatrix4x4& result);

    [[nodiscard]] static FloatingPointMatrix4x4
    CreateFromAxisAngle(const FloatingPointVector3<T>& axis, const Radian<T>& angle);

    /// Returns pointer to the first element.
    [[nodiscard]] const T* Data() const noexcept;

    /// Returns pointer to the first element.
    [[nodiscard]] T* Data() noexcept;

    static FloatingPointMatrix4x4 const Identity;
};

template <typename T>
FloatingPointMatrix4x4<T> const FloatingPointMatrix4x4<T>::Identity = {
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1,
};

template <typename T>
FloatingPointMatrix4x4<T> POMDOG_EXPORT
operator*(T scaleFactor, const FloatingPointMatrix4x4<T>& matrix) noexcept;

} // namespace Pomdog::Detail
