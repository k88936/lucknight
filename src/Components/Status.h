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
};

#endif //STATUSPLAYER_H
