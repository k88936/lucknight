//
// Created by root on 7/7/25.
//

#ifndef PREFABPROJECTILE_H
#define PREFABPROJECTILE_H
#include "Prefab.h"


class   PrefabProjectile : Prefab
{
public:
    float scale = 0.4f;
    float damage = 10;
    float lifeLeft = 10;
    float mass = 10;
    float density=3;
    float initImpulse = 10.0f;
    entt::entity build(const Matrix& transform) override;
};


#endif //PREFABPROJECTILE_H
