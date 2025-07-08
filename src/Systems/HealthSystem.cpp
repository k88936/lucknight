//
// Created by root on 7/7/25.
//

#include "HealthSystem.h"
#include "entt/entt.hpp"

#include "../Components/Types.h"
#include "../Components/Status.h"
#include "../Events/ProjectileHitEvent.h"
#include "../Managers/EventManager.h"

HealthSystem::HealthSystem()
{
    EventManager::getInstance().dispatcher.sink<ProjectileHitEvent>().connect<&HealthSystem::onHit>(this);
}

HealthSystem::~HealthSystem()
{
    EventManager::getInstance().dispatcher.sink<ProjectileHitEvent>().disconnect<&HealthSystem::onHit>(this);
}

void HealthSystem::onHit(const ProjectileHitEvent& event)
{
    auto& registry = World::getInstance().registry;
    assert((registry.all_of<TypePlayer,StatusPlayer>(event.target)));
    assert((registry.all_of<TypeProjectile,StatusProjectile>(event.projectile)));
    // registry.patch<>()
}

void HealthSystem::update()
{
    auto& registry = World::getInstance().registry;
    EventManager::getInstance().dispatcher.update<ProjectileHitEvent>();

}
