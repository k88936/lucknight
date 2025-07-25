//
// Created by root on 7/5/25.
//

#include "PlayerScript.h"

#include "IndicatorScript.h"
#include "../Components/Attachment.h"
#include "../Components/Body.h"
#include "../Components/Transform.h"
#include "../Events/MoverEvents.h"
#include "../Events/WeaponShootEvent.h"
#include "../Prefab/PrefabWeapon.h"
#include "../Utils/Wrapper.h"
#include "box2d/box2d.h"
#include "Buff/Buffs.h"


PlayerScript::PlayerScript()
{
    [[maybe_unused]] static bool register_on_death = []()
    {
        EventManager::getInstance().dispatcher.sink<DeathPlayer>().connect<&PlayerScript::onPlayerDeath>();
        return true;
    }();
}

void PlayerScript::onPlayerDeath(const DeathPlayer& event)
{
    auto& registry = World::getInstance().registry;
    const auto entity = event.player;
    assert(registry.all_of<PlayerScript>(entity));
    registry.patch<PlayerScript>(entity, [](PlayerScript& script)
    {
        script.stateMachine.switchState<PlayerStateMachine::Dead>();
    });
}

PlayerScript::~PlayerScript()
{
}

void PlayerScript::update()
{
    // Reset output forces/impulses
    // Update entity state based on input and current conditions
    stateMachine.update();


    auto& registry = World::getInstance().registry;
    registry.patch<IndicatorScript>(componentIndicator->entity, [this](IndicatorScript& indicator)
    {
        indicator.value = componentStatusPlayer->health / 100;
    });

    //jump
    if (componentInput->up && componentGroundDetector->got)
    {
        EventManager::getInstance().dispatcher.enqueue<MoverEvent>(MoverEvent{
            .entity = entity, .impulse = Vector(0, componentStatusPlayer->jump_impulse)
        });
    }

    //attack
    if (componentInput->attack)
    {
        if (const auto* const weapon = registry.try_get<Weapon>(entity))
        {
            EventManager::getInstance().dispatcher.enqueue<WeaponShootEvent>(WeaponShootEvent{
                .shooter = entity,
                .weapon = weapon->entity
            });
        }
    }
    //terrain buff
    if (componentGroundDetector->got)
    {
        assert(registry.all_of<StatusPlatform>(componentGroundDetector->target));
        const auto platformStatus = registry.get<StatusPlatform>(componentGroundDetector->target);
        switch (platformStatus.type)
        {
        case StatusPlatform::Grass:
            addTerrainEffect<BuffInvisibility>();
            break;
        case StatusPlatform::Soil:
            break;
        case StatusPlatform::Snow:
            addTerrainEffect<BuffSpeeding>();
            break;
        }
    }

    //use fist
    if (!registry.all_of<Weapon>(entity))
    {
        PrefabWeaponFist fist;
        registry.emplace<Weapon>(entity, Weapon{
                                     .entity = fist.build(componentTransform->matrix),
                                     .transform = {.offset = {0.4, -0.2}}
                                 });
    }
}


void PlayerScript::init()
{
    stateMachine.init<PlayerStateMachine::Idle>(this);
    componentTreasureDetector->enable = false;
}


void PlayerScript::PlayerStateMachine::Idle::onEnter(StateMachine<PlayerScript>* const stateMachine,
                                                     PlayerScript* const param)
{
    StateBase::onEnter(stateMachine, param);
    AnimationSystem::getInstance().play<Idle>(param->entity);
}


void PlayerScript::PlayerStateMachine::Idle::onUpdate(StateMachine<PlayerScript>* const stateMachine,
                                                      PlayerScript* const param)
{
    StateBase::onUpdate(stateMachine, param);
    if (param->componentInput->left || param->componentInput->right)
    {
        stateMachine->switchState<Moving>();
    }
    else if (param->componentInput->down)
    {
        stateMachine->switchState<Crouching>();
    }
}

void PlayerScript::PlayerStateMachine::Moving::onEnter(StateMachine<PlayerScript>* const stateMachine,
                                                       PlayerScript* const param)
{
    StateBase::onEnter(stateMachine, param);
    AnimationSystem::getInstance().play<Moving>(param->entity);
}

void PlayerScript::PlayerStateMachine::Moving::onUpdate(StateMachine<PlayerScript>* const stateMachine,
                                                        PlayerScript* const param)
{
    StateBase::onUpdate(stateMachine, param);
    float direction = 0;
    if (param->componentInput->left)
    {
        direction = -1;
    }
    else if (param->componentInput->right)
    {
        direction = 1;
    }
    else
    {
        stateMachine->switchState<Idle>();
        return;
    }
    param->componentTransform->matrix.updateFlip(direction);
    EventManager::getInstance().dispatcher.enqueue<MoverEvent>({
        .entity = param->entity, .force = Vector(direction * param->componentStatusPlayer->move_force, 0)
    });
}

void PlayerScript::PlayerStateMachine::Crouching::onEnter(StateMachine* const stateMachine,
                                                          PlayerScript* const param)
{
    StateBase::onEnter(stateMachine, param);
    param->componentTreasureDetector->enable = true;
    EventManager::getInstance().dispatcher.enqueue<AddBuff<BuffCrouching>>(param->entity);
}

void PlayerScript::PlayerStateMachine::Crouching::onUpdate(StateMachine* stateMachine,
                                                           PlayerScript* param)
{
    StateBase::onUpdate(stateMachine, param);
    if (!param->componentInput->down)
    {
        stateMachine->switchState<Idle>();
    }
    else if (param->componentInput->left || param->componentInput->right)
    {
        stateMachine->switchState<Moving>();
    }
}

void PlayerScript::PlayerStateMachine::Crouching::onExit(StateMachine<PlayerScript>* const stateMachine,
                                                         PlayerScript* const param)
{
    StateBase::onExit(stateMachine, param);
    param->componentTreasureDetector->enable = false;
    EventManager::getInstance().dispatcher.enqueue<RemoveBuff<BuffCrouching>>(param->entity);
}

void PlayerScript::PlayerStateMachine::Dead::onEnter(StateMachine* const stateMachine,
                                                     PlayerScript* const param)
{
    StateBase::onEnter(stateMachine, param);
    AnimationSystem::getInstance().play<Dead>(param->entity);
}
