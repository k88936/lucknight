//
// Created by kvtoD on 7/24/2025.
//

#ifndef BUFFS_H
#define BUFFS_H
#include "BuffBase.h"
#include "TimingBuff.h"
#include "../PlayerScript.h"
#include "../../Components/Body.h"
#include "box2d/box2d.h"

BUFF(BuffCrouching, (Body))
{
    float dampingBak{};
    void onEnter() override
    {
        auto& registry = World::getInstance().registry;
        dampingBak = b2Body_GetLinearDamping(componentBody->bodyID);
        b2Body_SetLinearDamping(componentBody->bodyID, dampingBak * 100);
    }

    void onExit() override
    {
        auto& registry = World::getInstance().registry;
        b2Body_SetLinearDamping(componentBody->bodyID, dampingBak);
    }
};
#endif //BUFFS_H
