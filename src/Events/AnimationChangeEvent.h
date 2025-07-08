//
// Created by root on 7/6/25.
//

#ifndef ANIMATIONCHANGEEVENT_H
#define ANIMATIONCHANGEEVENT_H
#include "entt/core/fwd.hpp"
#include "entt/entity/entity.hpp"

struct AnimationChangeEvent {
    entt::entity entity;
    entt::id_type stateId;
};
#endif //ANIMATIONCHANGEEVENT_H
