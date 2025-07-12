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

    Texture* texture = TextureManager::getInstance().getTextures("assets/projectile/", 0, {.scale = scale});
    registry.emplace<Drawable>(entity, Drawable{.texture = texture});

    registry.emplace<StatusProjectile>(entity, StatusProjectile{.damage = 10, .lifeLeft = 10.0f});
    registry.emplace<ProjectileScript>(entity);

    registry.emplace<TypeProjectile>(entity);

    registry.emplace<Body>(entity);
    return entity;
}
