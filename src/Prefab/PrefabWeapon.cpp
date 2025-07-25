//
// Created by root on 7/9/25.
//

#include "PrefabWeapon.h"

#include "../Components/Drawable.h"
#include "../Components/Status.h"
#include "../Core/World.h"
#include "PrefabProjectile.h"
#include "../Components/Types.h"
#include "../Events/BodyEvents.h"
#include "../Managers/EventManager.h"
#include "../Managers/TextureManager.h"

struct Texture;

entt::entity PrefabWeapon::build(const Matrix& transform)
{
    auto& registry = World::getInstance().registry;

    const auto entity = Prefab::build(transform);


    registry.emplace<StatusWeapon>(entity, StatusWeapon{
                                       .ammoLeft = ammoCapability, .accuracy = accuracy, .delay = delay,
                                       .ammoType = ammoType, .emmitDirection = emmitDirection, .emmitPoint = emmitPoint
                                   });
    registry.emplace<TypeWeapon>(entity);
    return entity;
}

entt::entity PrefabWeaponFist::build(const Matrix& transform)
{
    auto& registry = World::getInstance().registry;
    const auto& entity = PrefabWeapon::build(transform);
    registry.emplace<Drawable>(entity, Drawable{
                                   .texture = (TextureManager::getInstance().getTexture(
                                       "assets/weapon/weapons5_2.png",  {.scale = scale}))
                               });
    return entity;
}

entt::entity PrefabWeaponKnife::build(const Matrix& transform)
{
    auto& registry = World::getInstance().registry;
    const auto& entity = PrefabWeapon::build(transform);
    registry.emplace<Drawable>(entity, Drawable{
                                   .texture = (TextureManager::getInstance().getTexture(
                                       "assets/weapon/weapons_110.png",  {.scale =scale}))
                               });
    return entity;
}

entt::entity PrefabWeaponBall::build(const Matrix& transform)
{
    auto& registry = World::getInstance().registry;
    const auto& entity = PrefabWeapon::build(transform);
    registry.emplace<Drawable>(entity, Drawable{
                                   .texture = (TextureManager::getInstance().getTexture(
                                       "assets/weapon/weapons2_113.png",  {.scale = scale}))
                               });
    return entity;
}

entt::entity PrefabWeaponGun::build(const Matrix& transform)
{
    auto& registry = World::getInstance().registry;
    const auto& entity = PrefabWeapon::build(transform);
    registry.emplace<Drawable>(entity, Drawable{
                                   .texture = (TextureManager::getInstance().getTexture(
                                       "assets/weapon/weapons3_101.png",  {.scale = scale}))
                               });
    return entity;
}

entt::entity PrefabWeaponSniper::build(const Matrix& transform)
{
    auto& registry = World::getInstance().registry;
    const auto& entity = PrefabWeapon::build(transform);
    registry.emplace<Drawable>(entity, Drawable{
                                   .texture = (TextureManager::getInstance().getTexture(
                                       "assets/weapon/weapons3_81.png",  {.scale = scale}))
                               });
    return entity;
}
