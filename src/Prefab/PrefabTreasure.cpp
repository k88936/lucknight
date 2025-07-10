//
// Created by root on 7/10/25.
//

#include "PrefabTreasure.h"

#include "../Components/Body.h"
#include "../Components/Drawable.h"
#include "../Components/PhysicsDesciption.h"
#include "../Components/SpaceQuery.h"
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


    static Texture* texture = TextureManager::getInstance().getTextures("assets/treasure/", 0, {.scale = scale});
    registry.emplace<Drawable>(entity, Drawable{.texture = texture});

    registry.emplace<PhysicsDes_BoxShapeDesc>(entity, PhysicsDes_BoxShapeDesc{
                                                  .halfWidth = scale/2, .halfHeight = scale/2, .material = {.density = 3.0f}
                                              });
    registry.emplace<PhysicsDes_Movement>(entity, PhysicsDes_Movement{
                                              .type = PhysicsDes_Movement::Dynamic,
                                              .linearDamping = 0.5f,
                                              .rotationLocked = false,
                                              .contactCategoryBits = TypeTreasure::category(),
                                              .contactMaskBits = SpaceQuery<TypeTreasure>::category() |
                                              TypeProjectile::category()|TypePlatform::category()
                                          });
    registry.emplace<TypeTreasure>(entity);
    registry.emplace<Body>(entity);
    return entity;
}
