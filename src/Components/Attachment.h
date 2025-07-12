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
    bool followFlip = true;
};

struct Weapon
{
    entt::entity entity;
    relativeTransform transform;
};

// template <typename T>
struct Indicator
{
    entt::entity entity;
    relativeTransform transform;
};

#endif //ATTACHMENT_H
