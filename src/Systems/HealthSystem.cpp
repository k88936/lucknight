//
// Created by root on 7/7/25.
//

#include "HealthSystem.h"
#include "entt/entt.hpp"

#include "../Components/Types.h"
#include "../Components/Status.h"
#include "../Components/Transform.h"
#include "../Events/LifeEvents.h"
#include "../Events/ProjectileHitEvent.h"
#include "../Managers/EventManager.h"
#include "../Scripts/Buff/Buffs.h"

HealthSystem::HealthSystem()
{
    EventManager::getInstance().dispatcher.sink<ProjectileHitEvent>().connect<&HealthSystem::onHit>(this);
    EventManager::getInstance().dispatcher.sink<DeathPlayer>().connect<&HealthSystem::onDeathPlayer>(this);
}

HealthSystem::~HealthSystem()
{
    EventManager::getInstance().dispatcher.sink<ProjectileHitEvent>().disconnect<&HealthSystem::onHit>(this);
    EventManager::getInstance().dispatcher.sink<DeathPlayer>().disconnect<&HealthSystem::onDeathPlayer>(this);
}

void HealthSystem::onDeathPlayer(const DeathPlayer& event)
{
    auto& registry = World::getInstance().registry;
    // registry.destroy(event.player);
}

void HealthSystem::onHit(const ProjectileHitEvent& event)
{
    auto& registry = World::getInstance().registry;
    assert((registry.all_of<TypePlayer,StatusPlayer>(event.target)));
    assert((registry.all_of<TypeProjectile,StatusProjectile>(event.projectile)));
    float damage = registry.get<StatusProjectile>(event.projectile).damage;
    registry.patch<StatusPlayer>(event.target, [damage](StatusPlayer& playerStatus)
    {
        playerStatus.health -= damage;
    });
    EventManager::getInstance().dispatcher.enqueue<AddBuff<BuffHit>>({event.target});
}

void HealthSystem::update()
{
    auto& registry = World::getInstance().registry;
    EventManager::getInstance().dispatcher.update<ProjectileHitEvent>();

    constexpr float flag = -130724;
    {
        //kill when fall
        const auto view = registry.view<TypePlayer, StatusPlayer, Transform>();
        view.each([](const entt::entity, StatusPlayer& status, const Transform& transform)
        {
            if (status.health > 0 && transform.matrix.getPosition().y() < -5)
            {
                status.health = 0;
            }
        });
    }
    {
        const auto view = registry.view<TypePlayer, StatusPlayer>();
        view.each([](const entt::entity entity, StatusPlayer& status)
        {
            if (status.health == flag)
            {
                return;
            }
            if (status.health <= 0)
            {
                status.health = flag;
                EventManager::getInstance().dispatcher.enqueue<DeathPlayer>(entity);
            }
        });
    }

    EventManager::getInstance().dispatcher.update<DeathPlayer>();
}
