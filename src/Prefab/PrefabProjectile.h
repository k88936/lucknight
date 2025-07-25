//
// Created by root on 7/7/25.
//

#ifndef PREFABPROJECTILE_H
#define PREFABPROJECTILE_H
#include "Prefab.h"


class PrefabProjectile : Prefab
{
public:
    float scale = 1;
    float damage = 20;
    float life = 10;
    float density = 3;
    float initImpulse = 1.0f;
    float gravityScale = 0.1;
    entt::entity build(const Matrix& transform) override;
};

class PrefabProjectileEnergyBall : public PrefabProjectile
{
public:
    PrefabProjectileEnergyBall()
    {
        density = 1;
    }

    entt::entity build(const Matrix& transform) override;
};

class PrefabProjectileFlash : public PrefabProjectile
{
public:
    PrefabProjectileFlash()
    {
        initImpulse = 8;
        density = 2;
        damage = 50;
    }

    entt::entity build(const Matrix& transform) override;
};

class PrefabProjectileFist : public PrefabProjectile
{
public:
    PrefabProjectileFist()
    {
        initImpulse = 1;
        damage = 10;
        gravityScale = 0;
        density = 10;
        life = 0.1;
    }

    entt::entity build(const Matrix& transform) override;
};

class PrefabProjectileBall : public PrefabProjectile
{
public:
    PrefabProjectileBall()
    {
        gravityScale = 1;
        density = 10;
        initImpulse = 3;
    }

    entt::entity build(const Matrix& transform) override;
};
class PrefabProjectileKnife : public  PrefabProjectile
{
public:
    PrefabProjectileKnife()
    {
        gravityScale=0;
        life = 0.3;
        damage = 30;
        initImpulse = 2;
    }
    entt::entity build(const Matrix& transform) override;
};
#endif //PREFABPROJECTILE_H

