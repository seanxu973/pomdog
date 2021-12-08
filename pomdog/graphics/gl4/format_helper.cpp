// Copyright mogemimi. Distributed under the MIT license.

#include "pomdog/graphics/gl4/format_helper.hpp"
#include "pomdog/basic/unreachable.hpp"
#include "pomdog/graphics/comparison_function.hpp"

namespace pomdog::detail::gl4 {

GLenum ToComparisonFunctionGL4NonTypesafe(ComparisonFunction comparison) noexcept
{
    switch (comparison) {
    case ComparisonFunction::Always:
        return GL_ALWAYS;
    case ComparisonFunction::Equal:
        return GL_EQUAL;
    case ComparisonFunction::Greater:
        return GL_GREATER;
    case ComparisonFunction::GreaterEqual:
        return GL_GEQUAL;
    case ComparisonFunction::Less:
        return GL_LESS;
    case ComparisonFunction::LessEqual:
        return GL_LEQUAL;
    case ComparisonFunction::Never:
        return GL_NEVER;
    case ComparisonFunction::NotEqual:
        return GL_NOTEQUAL;
    }
    POMDOG_UNREACHABLE("Unsupported comparison function");
}

} // namespace pomdog::detail::gl4
