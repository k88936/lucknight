//
// Created by kvtoD on 6/30/2025.
//

#include "PrefabPlayer.h"

#include "PrefabIndicator.h"
#include "Texture.h"
#include "../Core/World.h"
#include "../Components/Drawable.h"
#include "../Components/Keymap.h"
#include "../Components/Input.h"
#include "../Components/PhysicsDesciption.h"
#include "../Components/Animator.h"
#include "../Components/Attachment.h"
#include "../Components/Body.h"
#include "../Components/SpaceQuery.h"
#include "../Components/Status.h"
#include "../Components/Tags.h"
#include "../Components/Types.h"
#include "../Events/BodyEvents.h"
#include "../Events/KeyEvents.h"
#include "../Managers/EventManager.h"
#include "../Managers/TextureManager.h"
#include "../Scripts/PlayerScript.h"

#include "../Systems/AnimationSystem.h"

entt::entity PrefabPlayer::build(const Matrix& transform)
{
    const auto entity = Prefab::build(transform);
    auto& registry = World::getInstance().registry;

    constexpr float halfHeight = 0.8f;
    // Add physics components
    registry.emplace<PhysicsDes_CapsuleShapeDesc>(entity, PhysicsDes_CapsuleShapeDesc{
                                                      .halfHeight = halfHeight,
                                                      .radius = 0.5f,
                                                      .material = {.friction = 0.1f}
                                                  });

    registry.emplace<PhysicsDes_Movement>(entity, PhysicsDes_Movement{
                                              .type = PhysicsDes_Movement::Dynamic,
                                              .contactCategoryBits = TypePlayer::category(),
                                              .contactMaskBits = SpaceQuery<TypePlayer>::category() |
                                              TypePlayer::category()
                                              | TypePlatform::category() |
                                              TypeProjectile::category()
                                          });

    // Add input components
    registry.emplace<Keymap>(entity, keymap);
    registry.emplace<Input>(entity);
    registry.emplace<StatusPlayer>(entity, StatusPlayer(100, 5.0f, 8.0f));
    registry.emplace<Drawable>(entity, Drawable{.texture = nullptr});
    registry.emplace<Animator>(entity);
    registry.emplace<PlayerScript>(entity);
    registry.emplace<GroundDetector>(entity, GroundDetector{.offset = {0, -halfHeight}, .radius = 0.05f});
    registry.emplace<TreasureDetector>(entity, TreasureDetector{.radius = 0.5f});

    static PrefabIndicator* prefabIndicator = []()
    {
        auto* result = new PrefabIndicator();
        result->textures = TextureManager::getInstance().getAllTextures("assets/ui/indicator/blood", {.scale = 0.2});
        return result;
    }();
    registry.emplace<Indicator>(entity, Indicator{
                                    .entity = prefabIndicator->build(transform),
                                    .transform = {.offset = {0, 1}, .followFlip = false}
                                });

    AnimationSystem::getInstance().registerAnimation<PlayerScript::PlayerStateMachine::Idle>(
        entity, "assets/player/idle", {.scale = 2 * halfHeight});
    AnimationSystem::getInstance().registerAnimation<PlayerScript::PlayerStateMachine::Moving>(
        entity, "assets/player/move", {.scale = 2 * halfHeight});

    registry.emplace<TypePlayer>(entity);

    registry.emplace<Body>(entity);
    return entity;
}
