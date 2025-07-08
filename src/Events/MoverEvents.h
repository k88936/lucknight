//
// Created by root on 7/8/25.
//

#ifndef MOVEREVENTS_H
#define MOVEREVENTS_H
#include "entt/entity/entity.hpp"
#include "../Type/Vector.h"

struct  MoverEvent
{
    entt::entity entity;
    Vector force;
    Vector impulse;
};

#endif //MOVEREVENTS_H
