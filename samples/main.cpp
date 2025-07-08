// SPDX-FileCopyrightText: 2022 Erin Catto
// SPDX-License-Identifier: MIT

#include "sample.h"
#include "boot.h"

#include "box2d/box2d.h"
#include "box2d/math_functions.h"

#include <GLFW/glfw3.h>

#include "../src/Core/World.h"
#include "../src/Systems/PhysicsSystem.h"

class MyWorld : public Sample
{
public:
    explicit MyWorld(SampleContext* context)
        : Sample(context)
    {
        if (m_context->restart == false)
        {
            m_context->camera.m_center = {0, 0};
            m_context->camera.m_zoom = 25.0f * 1.0f;
        }
        World::getInstance().init();
        m_worldId = PhysicsSystem::getInstance().worldId;
    }

    void Step() override
    {
        World::getInstance().update();
        Sample::Step();
    }

    static Sample* Create(SampleContext* context)
    {
        return new MyWorld(context);
    }
};

static int sampleMyWorld = RegisterSample("World", "My World", MyWorld::Create);

int main()
{
   return boot(0,nullptr);
}
