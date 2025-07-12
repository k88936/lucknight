//
// Created by root on 7/5/25.
//

#include "PlayerScript.h"

#include "IndicatorScript.h"
#include "../Components/Attachment.h"
#include "../Components/Transform.h"
#include "../Events/MoverEvents.h"
#include "../Events/WeaponShootEvent.h"

PlayerScript::PlayerScript()
{
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
        indicator.value = componentStatusPlayer->health;
    });
    //jump
    if (componentInput->up && componentGroundDetector->got)
    {
        EventManager::getInstance().dispatcher.enqueue<MoverEvent>(MoverEvent{
            .entity = entity, .impulse = Vector(0, componentStatusPlayer->jump_impulse)
        });
    }
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
}

void PlayerScript::init()
{
    stateMachine.init<PlayerStateMachine::Idle>(this);
}


void PlayerScript::PlayerStateMachine::Idle::onUpdate(StateMachine<PlayerScript>* const stateMachine,
                                                      PlayerScript* const param)
{
    StateBase::onUpdate(stateMachine, param);
    if (param->componentInput->left || param->componentInput->right)
    {
        stateMachine->switchState<PlayerStateMachine::Moving>();
    }
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
        stateMachine->switchState<PlayerStateMachine::Idle>();
        return;
    }
    param->componentTransform->matrix.updateFlip(direction);
    EventManager::getInstance().dispatcher.enqueue<MoverEvent>(MoverEvent{
        .entity = param->entity, .force = Vector(direction * param->componentStatusPlayer->move_force, 0)
    });
}

void PlayerScript::PlayerStateMachine::Dead::onEnter(StateMachine<PlayerScript>* const stateMachine,
                                                     PlayerScript* const param)
{
    StateBase::onEnter(stateMachine, param);
}
