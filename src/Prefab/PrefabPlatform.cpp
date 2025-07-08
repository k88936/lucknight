//
// Created by root on 7/6/25.
//

#include "PrefabPlatform.h"
#include "../Core/World.h"
#include "../Components/Drawable.h"
#include "../Components/PhysicsDesciption.h"
#include "../Components/SpaceQuery.h"
#include "../Components/Tags.h"
#include "../Components/Types.h"
#include "../Managers/TextureManager.h"

inline entt::entity PrefabPlatform::build(const Matrix& transform)
{
    const auto entity = Prefab::build(transform);
    auto& registry = World::getInstance().registry;

    constexpr float halfLen = 0.5f;
    // Add physics components
    registry.emplace<PhysicsDes_BoxShapeDesc>(entity, PhysicsDes_BoxShapeDesc{
                                                  .halfWidth = halfLen,
                                                  .halfHeight = halfLen,
                                                  .material = {.friction = 0.1f}
                                              });
    registry.emplace<PhysicsDes_Movement>(entity, PhysicsDes_Movement{
                                              .type = PhysicsDes_Movement::Static,

                                              .contactCategoryBits = TypePlatform::category(),
                                              .contactMaskBits = SpaceQuery<TypePlatform>::category() |
                                              TypePlayer::category() | TypeTreasure::category()
                                          });
    registry.emplace<TypePlatform>(entity);
    registry.emplace<TagBodyCreation>(entity);
    return entity;
}

entt::entity PrefabPlatform::build(const Matrix& transform, int imageIndex)
{
    auto& registry = World::getInstance().registry;
    const auto entity = build(transform);
    registry.emplace<Drawable>(entity, Drawable{
                                   .texture = TextureManager::getInstance().getTextures("assets/platform/static", imageIndex, {})
                               });
    return entity;
}
