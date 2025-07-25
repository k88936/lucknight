//
// Created by root on 7/9/25.
//

#ifndef PREFABWEAPON_H
#define PREFABWEAPON_H
#include "Prefab.h"
#include "PrefabProjectile.h"
#include "../Systems/WeaponSystem.h"


class PrefabWeapon : Prefab
{
public:
    entt::entity build(const Matrix& transform = Matrix()) override;
    int ammoCapability = 10;
    float accuracy = 1;
    float delay = 1;
    float scale=1;
    PrefabProjectile* ammoType = nullptr;
    Vector emmitPoint = {0.5, 0};
    Vector emmitDirection = {1, 0};
};

class PrefabWeaponFist : public PrefabWeapon
{
public:
    PrefabWeaponFist()
    {
        delay = 0.3;
        ammoCapability = WeaponSystem::MAGIC_INFINITY_AMMO;
        static PrefabProjectile* _ammoType = new PrefabProjectileFist();
        ammoType = _ammoType;
    }

    entt::entity build(const Matrix& transform = Matrix()) override;
};

class PrefabWeaponKnife : public PrefabWeapon
{
public:
    PrefabWeaponKnife()
    {
        delay = 0.3f;
        ammoCapability = WeaponSystem::MAGIC_INFINITY_AMMO;
        static PrefabProjectile* _ammoType = new PrefabProjectileKnife();
        ammoType = _ammoType;
    }

    entt::entity build(const Matrix& transform) override;
};

class PrefabWeaponBall : public PrefabWeapon
{
public:
    PrefabWeaponBall()
    {
        delay = 2;
        ammoCapability = 3;
        static PrefabProjectile* _ammoType = new PrefabProjectileBall();
        ammoType = _ammoType;
        emmitDirection = {1, 1};
    }
    entt::entity build(const Matrix& transform) override;
};
class PrefabWeaponGun : public  PrefabWeapon
{
public:
    PrefabWeaponGun()
    {
        delay = 0.1f;
        ammoCapability= 64;
        static PrefabProjectile *  _ammoType = new PrefabProjectileEnergyBall();
        ammoType = _ammoType;

    }
    entt::entity build(const Matrix& transform) override;
};
class PrefabWeaponSniper : public PrefabWeapon
{
public:
    PrefabWeaponSniper()
    {
        delay = 5;
        ammoCapability = 5;
        static PrefabProjectile * _ammoType = new PrefabProjectileFlash();
        ammoType = _ammoType;
    }
    entt::entity build(const Matrix& transform) override;
};

#endif //PREFABWEAPON_H
