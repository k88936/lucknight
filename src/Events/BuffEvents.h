//
// Created by kvtoD on 7/24/2025.
//

#ifndef BUFFEVENTS_H
#define BUFFEVENTS_H
#include "entt/entity/entity.hpp"
template <typename Buff>
struct AddBuff
{
    entt::entity entity;
    Buff buff;
};

template <typename Buff>
struct RemoveBuff
{
    entt::entity entity;
};

#endif //BUFFEVENTS_H
