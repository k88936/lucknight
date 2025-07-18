//
// Created by root on 7/7/25.
//

#ifndef STATUSPLAYER_H
#define STATUSPLAYER_H

#include "../Prefab//PrefabProjectile.h"

struct StatusPlayer
{
    float health;
    float move_force;
    float jump_impulse;

    float max_health;
    float max_move_force;
    float max_jump_impulse;

    StatusPlayer(float health, float move_force, float jump_impulse):
        health(health), move_force(move_force), jump_impulse(jump_impulse),

        max_health(health), max_move_force(move_force), max_jump_impulse(jump_impulse)
    {
    };
};

struct StatusProjectile
{
    float damage;
    float lifeLeft;
};

struct StatusWeapon
{
    int ammoLeft;
    float accuracy;
    float delay;
    float delayLeft;
    PrefabProjectile* ammoType;
    Vector emmitDirection = {1, 0};
    Vector emmitPoint = {0.5, 0};
};

#endif //STATUSPLAYER_H
