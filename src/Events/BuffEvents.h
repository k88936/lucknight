//
// Created by kvtoD on 7/24/2025.
//

#ifndef BUFFEVENTS_H
#define BUFFEVENTS_H
#include "entt/entity/entity.hpp"
class BuffBase;
template <typename Buff>
struct AddBuff
{
    entt::entity entity;

    explicit AddBuff(const entt::entity entity):entity(entity)
    {
        static_assert(std::is_base_of_v<BuffBase, Buff>);
        [[maybe_unused]] static bool force_registered = Buff::_register();
    }
};

template <typename Buff>
struct RemoveBuff
{
    entt::entity entity;
};

#endif //BUFFEVENTS_H
