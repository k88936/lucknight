//
// Created by root on 7/7/25.
//

#ifndef ATTACHMENT_H
#define ATTACHMENT_H
#include "../Type/Vector.h"
#include "entt/entity/entity.hpp"
struct relativeTransform
{
    Vector offset;
    bool flip=false;
};
struct Weapon
{
    entt::entity weaponEntity;
    relativeTransform transform;
};
#endif //ATTACHMENT_H
