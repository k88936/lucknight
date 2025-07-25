//
// Created by root on 7/7/25.
//

#include "PrefabProjectile.h"

#include "Texture.h"
#include "../../box2d/samples/draw.h"
#include "../Components/Body.h"
#include "../Components/Drawable.h"
#include "../Core/World.h"
#include "../Components/SpaceQuery.h"
#include "../Components/Types.h"
#include "../Components/Tags.h"
#include "../Components/PhysicsDesciption.h"
#include "../Events/BodyEvents.h"
#include "../Managers/EventManager.h"
#include "../Scripts/ProjectileScript.h"
#include "../Managers/TextureManager.h"


entt::entity PrefabProjectile::build(const Matrix& transform)
{
    auto& registry = World::getInstance().registry;
    const auto entity = Prefab::build(transform);
    registry.emplace<PhysicsDes_CircleShapeDesc>(entity, PhysicsDes_CircleShapeDesc{
                                                     .radius = scale / 2, .material = {.density = 3.0f}
                                                 });
    registry.emplace<PhysicsDes_Movement>(entity, PhysicsDes_Movement{
                                              .type = PhysicsDes_Movement::Dynamic,
                                              .isBullet = true,
                                              .linearDamping = 0,
                                              .rotationLocked = false,
                                              .gravityScale = gravityScale,
                                              .contactCategoryBits = TypeProjectile::category(),
                                              .contactMaskBits = SpaceQuery<TypeProjectile>::category() |
                                              TypePlayer::category()
                                          });


    registry.emplace<StatusProjectile>(entity, StatusProjectile{.damage = damage, .lifeLeft = life});
    registry.emplace<ProjectileScript>(entity);

    registry.emplace<TypeProjectile>(entity);

    registry.emplace<Body>(entity);
    return entity;
}

entt::entity PrefabProjectileEnergyBall::build(const Matrix& transform)
{
    auto& registry = World::getInstance().registry;
    const auto entity = PrefabProjectile::build(transform);
    registry.emplace<Drawable>(entity, Drawable{
                                   .texture = (TextureManager::getInstance().getTexture(
                                       "assets/projectile/bullet_124.png", {.scale = scale}))
                               });
    return entity;
}

entt::entity PrefabProjectileFlash::build(const Matrix& transform)
{
    auto& registry = World::getInstance().registry;
    const auto entity = PrefabProjectile::build(transform);
    registry.emplace<Drawable>(entity, Drawable{
                                   .texture = (TextureManager::getInstance().getTexture(
                                       "assets/projectile/bullet_32.png", {.scale = scale}))
                               });
    return entity;
}

entt::entity PrefabProjectileFist::build(const Matrix& transform)
{
    auto& registry = World::getInstance().registry;
    const auto entity = PrefabProjectile::build(transform);
    registry.emplace<Drawable>(entity, Drawable{
                                   .texture = (TextureManager::getInstance().getTexture(
                                       "assets/projectile/weapons5_3.png", {.scale = scale}))
                               });
    return entity;
}

entt::entity PrefabProjectileBall::build(const Matrix& transform)
{
    auto& registry = World::getInstance().registry;
    const auto entity = PrefabProjectile::build(transform);
    registry.emplace<Drawable>(entity, Drawable{
                                   .texture = (TextureManager::getInstance().getTexture(
                                       "assets/projectile/weapons2_113.png", {.scale = scale}))
                               });
    return entity;
}

entt::entity PrefabProjectileKnife::build(const Matrix& transform)
{
    auto& registry = World::getInstance().registry;
    const auto entity = PrefabProjectile::build(transform);
    registry.emplace<Drawable>(entity, Drawable{
                                   .texture = (TextureManager::getInstance().getTexture(
                                       "assets/projectile/weapons_110.png", {.scale = scale}))
                               });
    return entity;
}
