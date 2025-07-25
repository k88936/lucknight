//
// Created by kvtoD on 7/24/2025.
//

#ifndef BUFFS_H
#define BUFFS_H
#include "BuffBase.h"
#include "TimingExpiredMixin.h"
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

BUFF(BuffHit, (Drawable)), TimingExpiredMixin
{

    void onEnter() override
    {
        componentDrawable->color = {1, 0.5, 0.5};
        // componentDrawable->colored = true;
    }

    void onUpdate() override
    {
        updateTiming();
    }

    void onExit() override
    {
        componentDrawable->color = {1, 1, 1};
        // componentDrawable->colored = false;
    }
    public:
    using TimingExpiredMixin::isExpired;

    BuffHit(): TimingExpiredMixin(0.3f)
    {
    }

};

BUFF(BuffSpeeding, (StatusPlayer)), TimingExpiredMixin
{
    using TimingExpiredMixin::isExpired;
    float moveForceBak{};

    void onEnter() override
    {
        moveForceBak = componentStatusPlayer->move_force;
        componentStatusPlayer->move_force = 4 * moveForceBak;
    }

    void onUpdate() override
    {
        updateTiming();
    }

    void onExit() override
    {
        componentStatusPlayer->move_force = moveForceBak;
    }
    public:
    BuffSpeeding(): TimingExpiredMixin(0.3f)
    {
    }

};

BUFF(BuffInvisibility, (Drawable)), TimingExpiredMixin
{
    using TimingExpiredMixin::isExpired;
    public:
    void onEnter() override
    {
        componentDrawable->alpha = 0.2f;
        // componentDrawable->colored=true;
    }

    void onUpdate() override
    {
        updateTiming();
    }

    void onExit() override
    {
        componentDrawable->alpha = 1;
    }
    BuffInvisibility(): TimingExpiredMixin(0.3f)
    {
    }


};
#endif //BUFFS_H
