// Copyright (c) 2013-2020 mogemimi. Distributed under the MIT license.

#pragma once

#include "Pomdog/Experimental/ECS/ComponentBuffer.hpp"
#include "Pomdog/Experimental/ECS/ComponentType.hpp"
#include "Pomdog/Experimental/ECS/Entity.hpp"
#include "Pomdog/Experimental/ECS/EntityDesc.hpp"
#include "Pomdog/Utility/Assert.hpp"
#include <array>
#include <bitset>
#include <cstdint>
#include <memory>
#include <type_traits>
#include <utility>
#include <vector>

namespace Pomdog::ECS::Detail {

template <std::uint8_t MaxComponentCapacity, typename T, typename... Components>
class EntityQuery;

namespace Helper {

template <std::uint8_t MaxComponentCapacity>
std::bitset<MaxComponentCapacity> ComponentMask()
{
    return std::bitset<MaxComponentCapacity>{};
}

template <std::uint8_t MaxComponentCapacity, typename Type, typename... Components>
std::bitset<MaxComponentCapacity> ComponentMask()
{
    const auto typeIndex = ComponentTypeDeclaration<Type>::GetTypeIndex();
    POMDOG_ASSERT(typeIndex < MaxComponentCapacity);

    auto mask = ComponentMask<MaxComponentCapacity, Components...>();
    mask[typeIndex] = true;
    return mask;
}

template <std::uint8_t MaxComponentCapacity, typename T>
T* GetComponent(
    const Entity& entity,
    std::vector<std::unique_ptr<ComponentBufferBase>>& components,
    std::vector<EntityDesc<MaxComponentCapacity>>& descriptions)
{
    const auto typeIndex = ComponentTypeDeclaration<T>::GetTypeIndex();
    POMDOG_ASSERT(typeIndex < MaxComponentCapacity);

    if (typeIndex >= components.size()) {
        return nullptr;
    }

    auto& entities = components[typeIndex];
    if (entities == nullptr) {
        return nullptr;
    }

    POMDOG_ASSERT(entity.GetIndex() < descriptions.size());
    auto& desc = descriptions[entity.GetIndex()];
    if (desc.IncremantalVersion != entity.GetVersion()) {
        return nullptr;
    }

    POMDOG_ASSERT(entities != nullptr);
    if (entity.GetIndex() >= entities->GetSize()) {
        return nullptr;
    }

    POMDOG_ASSERT(entity.GetIndex() < entities->GetSize());

    auto nativeEntities = static_cast<Detail::ComponentBuffer<T>*>(entities.get());
    POMDOG_ASSERT(nativeEntities != nullptr);
    POMDOG_ASSERT(nativeEntities == dynamic_cast<Detail::ComponentBuffer<T>*>(entities.get()));
    POMDOG_ASSERT(desc.ComponentBitMask[typeIndex]);
    return nativeEntities->GetComponent(entity.GetIndex());
}

} // namespace Helper

template <std::uint8_t MaxComponentCapacity, typename T, typename... Components>
class EntityQuery<MaxComponentCapacity, Entity, T, Components...> final {
public:
    EntityQuery() = delete;
    EntityQuery(const EntityQuery&) = delete;
    EntityQuery& operator=(const EntityQuery&) = delete;

    EntityQuery(EntityQuery&&) = default;
    EntityQuery& operator=(EntityQuery&&) = default;

    EntityQuery(
        std::vector<std::unique_ptr<ComponentBufferBase>>& componentsIn,
        std::vector<EntityDesc<MaxComponentCapacity>>& descriptionsIn)
        : components(componentsIn)
        , descriptions(descriptionsIn)
    {
    }

    template <typename Func>
    void ForEach(Func func)
    {
        const auto mask = Helper::ComponentMask<MaxComponentCapacity, T, Components...>();

        std::uint32_t index = 0;
        for (const auto& desc : descriptions) {
            if (desc.IsEnabled) {
                if ((desc.ComponentBitMask & mask) == mask) {
                    const Entity entity{desc.IncremantalVersion, index};
                    func(
                        entity,
                        *Helper::GetComponent<MaxComponentCapacity, T>(entity, components, descriptions),
                        *Helper::GetComponent<MaxComponentCapacity, Components>(entity, components, descriptions)...);
                }
            }
            ++index;
        }
    }

private:
    std::vector<std::unique_ptr<ComponentBufferBase>>& components;
    std::vector<EntityDesc<MaxComponentCapacity>>& descriptions;
};

template <std::uint8_t MaxComponentCapacity, typename T, typename... Components>
class EntityQuery final {
public:
    EntityQuery() = delete;
    EntityQuery(const EntityQuery&) = delete;
    EntityQuery& operator=(const EntityQuery&) = delete;

    EntityQuery(EntityQuery&&) = default;
    EntityQuery& operator=(EntityQuery&&) = default;

    EntityQuery(
        std::vector<std::unique_ptr<ComponentBufferBase>>& componentsIn,
        std::vector<EntityDesc<MaxComponentCapacity>>& descriptionsIn)
        : components(componentsIn)
        , descriptions(descriptionsIn)
    {
    }

    template <typename Func>
    void ForEach(Func func)
    {
        const auto mask = Helper::ComponentMask<MaxComponentCapacity, T, Components...>();

        std::uint32_t index = 0;
        for (const auto& desc : descriptions) {
            if (desc.IsEnabled) {
                if ((desc.ComponentBitMask & mask) == mask) {
                    const Entity entity{desc.IncremantalVersion, index};
                    func(
                        *Helper::GetComponent<MaxComponentCapacity, T>(entity, components, descriptions),
                        *Helper::GetComponent<MaxComponentCapacity, Components>(entity, components, descriptions)...);
                }
            }
            ++index;
        }
    }

private:
    std::vector<std::unique_ptr<ComponentBufferBase>>& components;
    std::vector<EntityDesc<MaxComponentCapacity>>& descriptions;
};

} // namespace Pomdog::ECS::Detail
