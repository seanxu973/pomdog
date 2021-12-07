// Copyright (c) 2013-2021 mogemimi. Distributed under the MIT license.

#include "pomdog/experimental/ecs/component_type_index.hpp"
#include "pomdog/utility/assert.hpp"

namespace Pomdog::ECS::Detail {

ComponentTypeIndex::IndexType ComponentTypeIndex::count = 0;

ComponentTypeIndex::IndexType ComponentTypeIndex::IncrementIndex()
{
    POMDOG_ASSERT(count < std::numeric_limits<IndexType>::max());
    ++count;
    POMDOG_ASSERT(count > 0);
    return count;
}

} // namespace Pomdog::ECS::Detail