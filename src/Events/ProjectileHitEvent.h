//
// Created by root on 7/7/25.
//

#ifndef DAMAGEEVENT_H
#define DAMAGEEVENT_H
#include "entt/entity/entity.hpp"

struct ProjectileHitEvent
{
    entt::entity projectile;
    entt::entity target;
};
#endif //DAMAGEEVENT_H
