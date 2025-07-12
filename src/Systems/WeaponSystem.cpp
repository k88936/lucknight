//
// Created by root on 7/9/25.
//

#include "WeaponSystem.h"

#include "../Components/Attachment.h"
#include "../Components/Status.h"
#include "../Components/Transform.h"
#include "../Components/Types.h"
#include "../Core/World.h"
#include "../Events/MoverEvents.h"
#include "../Managers/EventManager.h"

void WeaponSystem::update()
{
    EventManager::getInstance().dispatcher.update<WeaponShootEvent>();
    auto& registry = World::getInstance().registry;
    const auto view = registry.view<TypeWeapon, StatusWeapon>();
    view.each([](entt::entity entity, StatusWeapon& status)
        {
            if (status.delayLeft > 0)
            {
                status.delayLeft -= World::getInstance().getFixedDeltaTime();
            }
        }
    );
}

WeaponSystem::WeaponSystem()
{
    EventManager::getInstance().dispatcher.sink<WeaponShootEvent>().connect<&WeaponSystem::onShootEvent>(this);
    auto& registry = World::getInstance().registry;

    registry.on_destroy<Weapon>().connect<&WeaponSystem::onDestroyWeaponComponent>(this);
}

WeaponSystem::~WeaponSystem()
{
    EventManager::getInstance().dispatcher.disconnect(this);
    auto& registry = World::getInstance().registry;
    registry.on_destroy<Weapon>().disconnect(this);
}

void WeaponSystem::onDestroyWeaponComponent(const entt::entity entity)
{
    auto& registry = World::getInstance().registry;
    const Weapon& weapon = registry.get<Weapon>(entity);
    registry.destroy(weapon.entity);
}

void WeaponSystem::onShootEvent(const WeaponShootEvent& event)
{
    auto& registry = World::getInstance().registry;
    const auto entity = event.weapon;
    assert(registry.valid(entity));
    assert(registry.all_of<Weapon>(event.shooter));
    assert(registry.all_of<Transform>(entity));
    assert(registry.all_of<TypeWeapon>(entity));
    assert(registry.all_of<StatusWeapon>(entity));
    const auto& transform = registry.get<Transform>(entity);
    const auto& status = registry.get<StatusWeapon>(entity);
    if (status.ammoLeft <= 0)
    {
        // throw weapon
        registry.erase<Weapon>(event.shooter);
        return;
    }
    if (status.delayLeft > 0)
    {
        return;
    }
    registry.patch<StatusWeapon>(entity, [](StatusWeapon& weaponStatus)
    {
        weaponStatus.ammoLeft--;
        weaponStatus.delayLeft = weaponStatus.delay;
    });
    const entt::entity ammo = status.ammoType->build(transform.matrix.mapMatrix(status.emmitPoint,true));
    EventManager::getInstance().dispatcher.enqueue<MoverEvent>({
        .entity = ammo, .impulse = transform.matrix.localMapVector(status.emmitDirection) * status.ammoType->initImpulse
    });
}
