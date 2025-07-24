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
#include "../Events/LifeEvents.h"
#include "../Systems/AnimationSystem.h"
#include "StateMachine/StateMachine.h"
SCRIPT(PlayerScript, (Input)(Transform)(GroundDetector)(TreasureDetector)(StatusPlayer)(Indicator))
{
public:
    PlayerScript();
    ~PlayerScript() override;

    void update() override;
    void init() override;

    static void onPlayerDeath(const DeathPlayer & event);


    class PlayerStateMachine : public StateMachine<PlayerScript>
    {
    public:
        class Idle final : public StateBase
        {
            void onEnter(StateMachine* stateMachine, PlayerScript* param) override;

            void onUpdate(StateMachine* stateMachine, PlayerScript* param) override;
        };

        class Moving final : public StateBase
        {
            void onEnter(StateMachine* stateMachine, PlayerScript* param) override;

            void onUpdate(StateMachine* stateMachine, PlayerScript* param) override;
        };
        class Crouching final : public StateBase
        {
            void onEnter(StateMachine* stateMachine, PlayerScript* param) override;
            void onUpdate(StateMachine* stateMachine, PlayerScript* param) override;
            void onExit(StateMachine* stateMachine, PlayerScript* param) override;
        };

        class Dead final : public PlayerStateMachine::StateBase
        {
            void onEnter(StateMachine* stateMachine, PlayerScript* param) override;
        };
    } stateMachine;
};
#endif //PLAYERSCRIPT_H
