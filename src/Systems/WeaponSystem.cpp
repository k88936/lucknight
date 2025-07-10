//
// Created by root on 7/9/25.
//

#include "WeaponSystem.h"

#include "../Components/Status.h"
#include "../Components/Transform.h"
#include "../Components/Types.h"
#include "../Core/World.h"
#include "../Events/MoverEvents.h"
#include "../Managers/EventManager.h"

void WeaponSystem::update()
{
    EventManager::getInstance().dispatcher.update<WeaponShootEvent>();
}

WeaponSystem::WeaponSystem()
{
    EventManager::getInstance().dispatcher.sink<WeaponShootEvent>().connect<&WeaponSystem::onShootEvent>(this);
}

WeaponSystem::~WeaponSystem()
{
    EventManager::getInstance().dispatcher.sink<WeaponShootEvent>().disconnect(this);
}

void WeaponSystem::onShootEvent(const WeaponShootEvent& event)
{
    auto& registry = World::getInstance().registry;
    const auto entity = event.weapon;
    assert(registry.valid(entity));
    assert(registry.all_of<Transform>(entity));
    assert(registry.all_of<TypeWeapon>(entity));
    assert(registry.all_of<StatusWeapon>(entity));
    const auto& transform = registry.get<Transform>(entity);
    const auto& status = registry.get<StatusWeapon>(entity);
    if (status.ammoLeft <= 0)
    {
        // throw weapon
        return;
    }
    if (status.delayLeft > 0)
    {
        return;
    }
    registry.patch<StatusWeapon>(entity, [](StatusWeapon& status)
    {
        status.ammoLeft--;
        status.delayLeft = status.delay;
    });
    const entt::entity ammo = status.ammoType->build(transform.matrix);
    EventManager::getInstance().dispatcher.enqueue<MoverEvent>({
        .entity = ammo, .impulse = transform.matrix.getRotation() * status.ammoType->initImpulse
    });
}
