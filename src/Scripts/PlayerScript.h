//
// Created by root on 7/5/25.
//

#ifndef PLAYERSCRIPT_H
#define PLAYERSCRIPT_H
#include "Script.h"
#include "../Components/Attachment.h"
#include "../Components/Input.h"
#include "../Components/SpaceQuery.h"
#include "../Components/Status.h"
#include "../Components/Transform.h"
#include "../Components/Types.h"
#include "../Systems/AnimationSystem.h"
#include "StateMachine/StateMachine.h"
SCRIPT(PlayerScript, (Input)(Transform)(GroundDetector)(TreasureDetector)(StatusPlayer)(Indicator))
{
public:

    PlayerScript();
    ~PlayerScript() override;

    void update() override;
    void init() override;


    // Movement constants

    class PlayerStateMachine : public StateMachine<PlayerScript>
    {
    public:
        class Idle final : public PlayerStateMachine::StateBase
        {
            void onEnter(StateMachine<PlayerScript>* const stateMachine, PlayerScript* const param) override
            {
                StateBase::onEnter(stateMachine, param);
                AnimationSystem::getInstance().play<Idle>(param->entity);
            }

            void onUpdate(StateMachine<PlayerScript>* const stateMachine, PlayerScript* const param) override;
        };

        class Moving final : public PlayerStateMachine::StateBase
        {
            void onEnter(StateMachine<PlayerScript>* const stateMachine, PlayerScript* const param) override
            {
                StateBase::onEnter(stateMachine, param);
                AnimationSystem::getInstance().play<Moving>(param->entity);
            }

            void onUpdate(StateMachine<PlayerScript>* const stateMachine, PlayerScript* const param) override;
        };

        class Dead final : public PlayerStateMachine::StateBase
        {
            void onEnter(StateMachine<PlayerScript>* const stateMachine, PlayerScript* const param) override;
        };
    } stateMachine;
};
#endif //PLAYERSCRIPT_H
