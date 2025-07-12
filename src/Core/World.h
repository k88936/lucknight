//
// Created by kvtoD on 6/30/2025.
//

#ifndef WORLD_H
#define WORLD_H
#include "../Utils/Singletion.h"
#include "entt/entity/registry.hpp"


class World final : public Singleton<World>
{
public:
    entt::registry registry;
    void update();
    void init();
    // Get current time in seconds
    long getCurrentTimeMilliseconds();
    // Get delta time in seconds
    float getFrameDeltaTime() const
    {
        return deltaTime;
    }
    float getFixedDeltaTime() const
    {
        return 1.0f / 60.0f;
    }

private:
    long lastUpdateTime = 0;
    float deltaTime = 0;
};


#endif //WORLD_H
