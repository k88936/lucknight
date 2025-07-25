//
// Created by root on 7/6/25.
//

#include "PrefabPlatform.h"

#include "../Components/Attachment.h"
#include "../Components/Body.h"
#include "../Core/World.h"
#include "../Components/Drawable.h"
#include "../Components/PhysicsDesciption.h"
#include "../Components/SpaceQuery.h"
#include "../Components/Status.h"
#include "../Components/Tags.h"
#include "../Components/Transform.h"
#include "../Components/Types.h"
#include "../Events/BodyEvents.h"
#include "../Managers/EventManager.h"
#include "../Managers/TextureManager.h"

inline entt::entity PrefabPlatform::build(const Matrix& transform)
{
    const auto entity = Prefab::build(transform);
    auto& registry = World::getInstance().registry;

    // Add physics components
    registry.emplace<PhysicsDes_BoxShapeDesc>(entity, PhysicsDes_BoxShapeDesc{
                                                  .halfWidth = halfLen,
                                                  .halfHeight = halfLen,
                                                  .material = {.friction = 0.2f}
                                              });
    registry.emplace<PhysicsDes_Movement>(entity, PhysicsDes_Movement{
                                              .type = PhysicsDes_Movement::Static,
                                              .contactCategoryBits = TypePlatform::category(),
                                              .contactMaskBits = SpaceQuery<TypePlatform>::category() |
                                              TypePlayer::category() | TypeTreasure::category()
                                          });
    registry.emplace<TypePlatform>(entity);
    registry.emplace<Body>(entity);
    return entity;
}


entt::entity PrefabPlatformGrass::build(const Matrix& transform)
{
    auto& registry = World::getInstance().registry;
    const auto entity = PrefabPlatform::build(transform);


    const auto grass = registry.create();
    registry.emplace<Transform>(grass);
    registry.emplace<Drawable>(grass, Drawable{
                                   .texture = TextureManager::getInstance().getTextures(
                                       "assets/environment", TextureManager::MAGIC_RANDOM_INDEX,
                                       {.scale = halfLen / 0.5f})
                               }

    );

    registry.emplace<Drawable>(entity, Drawable{
                                   .texture = TextureManager::getInstance().getTextures(
                                       "assets/platform/static/grass", TextureManager::MAGIC_RANDOM_INDEX,
                                       {.scale = halfLen / 0.5f})
                               });
    registry.emplace<StatusPlatform>(entity, StatusPlatform{.type = StatusPlatform::Grass});
    registry.emplace<TextureOnly>(entity, TextureOnly{
                                      .entity = grass,
                                      .transform = {
                                          .offset = {0, 2 * halfLen}
                                      }
                                  });
    return entity;
}

entt::entity PrefabPlatformSoil::build(const Matrix& transform)
{
    auto& registry = World::getInstance().registry;
    const auto entity = PrefabPlatform::build(transform);

    registry.emplace<Drawable>(entity, Drawable{
                                   .texture = TextureManager::getInstance().getTextures(
                                       "assets/platform/static/soil", TextureManager::MAGIC_RANDOM_INDEX,
                                       {.scale = halfLen / 0.5f})
                               });
    registry.emplace<StatusPlatform>(entity, StatusPlatform{.type = StatusPlatform::Soil});
    return entity;
}

entt::entity PrefabPlatformSnow::build(const Matrix& transform)
{
    auto& registry = World::getInstance().registry;
    const auto entity = PrefabPlatform::build(transform);
    registry.emplace<Drawable>(entity, Drawable{
                                   .texture = TextureManager::getInstance().getTextures(
                                       "assets/platform/static/snow", TextureManager::MAGIC_RANDOM_INDEX,
                                       {.scale = halfLen / 0.5f})
                               });
    registry.emplace<StatusPlatform>(entity, StatusPlatform{.type = StatusPlatform::Snow});

    registry.patch<PhysicsDes_BoxShapeDesc>(entity, [](PhysicsDes_BoxShapeDesc& desc)
    {
        desc.material.friction = 0;
    });

    return entity;
}
