//
// Created by root on 7/7/25.
//

#include "ProjectileScript.h"

void ProjectileScript::update()
{
    componentStatusProjectile->lifeLeft -= World::getInstance().getFixedDeltaTime();
    auto& registry = World::getInstance().registry;
    if (componentStatusProjectile->lifeLeft <= 0)
    {
        registry.destroy(entity);
    }
}

void ProjectileScript::init()
{
}
