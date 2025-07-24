//
// Created by kvtoD on 7/24/2025.
//

#ifndef BUFFSYSTEM_H
#define BUFFSYSTEM_H
#include "System.h"
#include "../Core/World.h"
#include "../Events/BuffEvents.h"
#include "../Managers/EventManager.h"


class BuffSystem final : public System<BuffSystem>
{
public:
    template <typename... S>
    void registerBuff();
    BuffSystem();
    void update() override;
    ~BuffSystem() override;
    std::vector<std::function<void()>> updateBuffs;
    std::vector<std::function<void()>> eventBuffs;
    template <typename... B>
    void onAddBuff(const AddBuff<std::tuple_element_t<0, std::tuple<B...>>>& event);
    template <typename... B>
    void onRemoveBuff(const RemoveBuff<std::tuple_element_t<0, std::tuple<B...>>>& event);
};

template <typename... S>
void BuffSystem::registerBuff()
{
    using BuffType = std::tuple_element_t<0, std::tuple<S...>>;
    updateBuffs.emplace_back([]
    {
        auto& registry = World::getInstance().registry;
        for (const auto view = registry.view<S...>(); const auto entity : view)
        {
            BuffType& buff = registry.get<BuffType>(entity);
            if (buff.isExpired())
            {
                EventManager::getInstance().dispatcher.enqueue<RemoveBuff<BuffType>>({entity});
            }
            else
                buff.aux_update(entity);
        }
    });
    EventManager::getInstance().dispatcher.sink<AddBuff<BuffType>>()
                               .template connect<&BuffSystem::onAddBuff<S...>>(this);
    EventManager::getInstance().dispatcher.sink<RemoveBuff<BuffType>>()
                               .template connect<&BuffSystem::onRemoveBuff<S...>>(this);
    eventBuffs.emplace_back([]
    {
        EventManager::getInstance().dispatcher.update<AddBuff<BuffType>>();
        EventManager::getInstance().dispatcher.update<RemoveBuff<BuffType>>();
    });
}

template <typename... B>
void BuffSystem::onAddBuff(const AddBuff<std::tuple_element_t<0, std::tuple<B...>>>& event)
{
    using BuffType = std::tuple_element_t<0, std::tuple<B...>>;
    auto& registry = World::getInstance().registry;
    registry.emplace<BuffType>(event.entity);
    registry.get<BuffType>(event.entity).aux_enter(event.entity);
}

template <typename... B>
void BuffSystem::onRemoveBuff(const RemoveBuff<std::tuple_element_t<0, std::tuple<B...>>>& event)
{
    using BuffType = std::tuple_element_t<0, std::tuple<B...>>;
    auto& registry = World::getInstance().registry;
    registry.get<BuffType>(event.entity).aux_exit(event.entity);
    registry.remove<BuffType>(event.entity);
}


#endif //BUFFSYSTEM_H
