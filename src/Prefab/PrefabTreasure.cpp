//
// Created by root on 7/10/25.
//

#include "PrefabTreasure.h"

#include "../Components/Body.h"
#include "../Components/Drawable.h"
#include "../Components/PhysicsDesciption.h"
#include "../Components/SpaceQuery.h"
#include "../Components/Status.h"
#include "../Components/Types.h"
#include "../Core/World.h"
#include "../Events/BodyEvents.h"
#include "../Managers/EventManager.h"
#include "../Managers/TextureManager.h"

struct Texture;
float scale = 0.8f;

entt::entity PrefabTreasure::build(const Matrix& transform)
{
    auto& registry = World::getInstance().registry;
    const auto entity = Prefab::build(transform);


    registry.emplace<PhysicsDes_BoxShapeDesc>(entity, PhysicsDes_BoxShapeDesc{
                                                  .halfWidth = scale / 2, .halfHeight = scale / 2,
                                                  .material = {.density = 3.0f}
                                              });
    registry.emplace<PhysicsDes_Movement>(entity, PhysicsDes_Movement{
                                              .type = PhysicsDes_Movement::Dynamic,
                                              .linearDamping = 0.5f,
                                              .rotationLocked = false,
                                              .contactCategoryBits = TypeTreasure::category(),
                                              .contactMaskBits = SpaceQuery<TypeTreasure>::category() |
                                              TypeProjectile::category() | TypePlatform::category()
                                          });
    registry.emplace<TypeTreasure>(entity);
    registry.emplace<StatusTreasure>(entity, StatusTreasure{.type = type});
    registry.emplace<Body>(entity);
    return entity;
}

entt::entity PrefabTreasureWeapon::build(const Matrix& transform)
{
    auto& registry = World::getInstance().registry;
    const auto entity = PrefabTreasure::build(transform);
    registry.emplace<Drawable>(entity, Drawable{
                                   .texture = (TextureManager::getInstance().getTexture(
                                       "assets/treasure/objects_common_61.png", {.scale = scale}))
                               });
    return entity;
}

entt::entity PrefabTreasureCarrot::build(const Matrix& transform)
{
    auto& registry = World::getInstance().registry;
    const auto entity = PrefabTreasure::build(transform);
    registry.emplace<Drawable>(entity, Drawable{
                                   .texture = (TextureManager::getInstance().getTexture(
                                       "assets/treasure/objects_pickable_64.png", {.scale = scale}))
                               });
    return entity;
}

entt::entity PrefabTreasureRed::build(const Matrix& transform)
{
    auto& registry = World::getInstance().registry;
    const auto entity = PrefabTreasure::build(transform);
    registry.emplace<Drawable>(entity, Drawable{
                                   .texture = (TextureManager::getInstance().getTexture(
                                       "assets/treasure/weapons3_19.png", {.scale = scale}))
                               });
    return entity;
}

entt::entity PrefabTreasureBlue::build(const Matrix& transform)
{
    auto& registry = World::getInstance().registry;
    const auto entity = PrefabTreasure::build(transform);
    registry.emplace<Drawable>(entity, Drawable{
                                   .texture = (TextureManager::getInstance().getTexture(
                                       "assets/treasure/weapons3_20.png", {.scale = scale}))
                               });
    return entity;
}
