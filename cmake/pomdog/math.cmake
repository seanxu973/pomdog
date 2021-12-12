source_group(math           REGULAR_EXPRESSION "pomdog/math/*")
source_group(math/detail    REGULAR_EXPRESSION "pomdog/math/detail/*")

target_sources(pomdog_static PRIVATE
    # NOTE: math
    ${POMDOG_SRC_DIR}/math/bounding_box.cpp
    ${POMDOG_SRC_DIR}/math/bounding_box.hpp
    ${POMDOG_SRC_DIR}/math/bounding_box2d.cpp
    ${POMDOG_SRC_DIR}/math/bounding_box2d.hpp
    ${POMDOG_SRC_DIR}/math/bounding_circle.cpp
    ${POMDOG_SRC_DIR}/math/bounding_circle.hpp
    ${POMDOG_SRC_DIR}/math/bounding_frustum.cpp
    ${POMDOG_SRC_DIR}/math/bounding_frustum.hpp
    ${POMDOG_SRC_DIR}/math/bounding_sphere.cpp
    ${POMDOG_SRC_DIR}/math/bounding_sphere.hpp
    ${POMDOG_SRC_DIR}/math/color.cpp
    ${POMDOG_SRC_DIR}/math/color.hpp
    ${POMDOG_SRC_DIR}/math/containment_type.hpp
    ${POMDOG_SRC_DIR}/math/degree.hpp
    ${POMDOG_SRC_DIR}/math/forward_declarations.hpp
    ${POMDOG_SRC_DIR}/math/math.cpp
    ${POMDOG_SRC_DIR}/math/math.hpp
    ${POMDOG_SRC_DIR}/math/matrix2x2.cpp
    ${POMDOG_SRC_DIR}/math/matrix2x2.hpp
    ${POMDOG_SRC_DIR}/math/matrix3x2.cpp
    ${POMDOG_SRC_DIR}/math/matrix3x2.hpp
    ${POMDOG_SRC_DIR}/math/matrix3x3.cpp
    ${POMDOG_SRC_DIR}/math/matrix3x3.hpp
    ${POMDOG_SRC_DIR}/math/matrix4x4.cpp
    ${POMDOG_SRC_DIR}/math/matrix4x4.hpp
    ${POMDOG_SRC_DIR}/math/plane_intersection_type.hpp
    ${POMDOG_SRC_DIR}/math/plane.cpp
    ${POMDOG_SRC_DIR}/math/plane.hpp
    ${POMDOG_SRC_DIR}/math/point2d.cpp
    ${POMDOG_SRC_DIR}/math/point2d.hpp
    ${POMDOG_SRC_DIR}/math/point3d.cpp
    ${POMDOG_SRC_DIR}/math/point3d.hpp
    ${POMDOG_SRC_DIR}/math/quaternion.cpp
    ${POMDOG_SRC_DIR}/math/quaternion.hpp
    ${POMDOG_SRC_DIR}/math/radian.hpp
    ${POMDOG_SRC_DIR}/math/ray.cpp
    ${POMDOG_SRC_DIR}/math/ray.hpp
    ${POMDOG_SRC_DIR}/math/rectangle.cpp
    ${POMDOG_SRC_DIR}/math/rectangle.hpp
    ${POMDOG_SRC_DIR}/math/vector2.cpp
    ${POMDOG_SRC_DIR}/math/vector2.hpp
    ${POMDOG_SRC_DIR}/math/vector3.cpp
    ${POMDOG_SRC_DIR}/math/vector3.hpp
    ${POMDOG_SRC_DIR}/math/vector4.cpp
    ${POMDOG_SRC_DIR}/math/vector4.hpp
    ${POMDOG_SRC_DIR}/math/detail/tagged_arithmetic.hpp
    ${POMDOG_SRC_DIR}/math/detail/type_traits.hpp
)
