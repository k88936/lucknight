//
// Created by root on 7/11/25.
//


#include <qvariant.h>
#include "TreasureSystem.h"
#include "../Components/Attachment.h"
#include "../Components/Status.h"
#include "../Components/Transform.h"
#include "../Components/Types.h"
#include "../Core/World.h"
#include "../Events/BuffEvents.h"
#include "../Events/GainEvents.h"
#include "../Managers/EventManager.h"
#include "../Prefab/PrefabWeapon.h"
#include "../Scripts/Buff/Buffs.h"

TreasureSystem::TreasureSystem()
{
    EventManager::getInstance().dispatcher.sink<GainTreasure>().connect<&TreasureSystem::onGainTreasureEvent>(this);
}

TreasureSystem::~TreasureSystem()
{
    EventManager::getInstance().dispatcher.sink<GainTreasure>().disconnect<&TreasureSystem::onGainTreasureEvent>(this);
}

void TreasureSystem::update()
{
    EventManager::getInstance().dispatcher.update<GainTreasure>();
}

void TreasureSystem::onGainTreasureEvent(const GainTreasure& event)
{
    const auto treasure = event.treasure;
    auto& registry = World::getInstance().registry;
    const auto gainer = event.gainer;
    assert(registry .all_of<TypePlayer>(gainer));
    assert(registry.valid(gainer));
    assert(registry.valid(treasure));
    assert(registry.all_of<StatusTreasure>(treasure));

    StatusTreasure& status = registry.get<StatusTreasure>(treasure);

    switch (status.type)
    {
    case StatusTreasure::Weapon:
        {
            static std::vector<PrefabWeapon*> credits = {
                new PrefabWeaponBall(), new PrefabWeaponGun(), new PrefabWeaponKnife(), new PrefabWeaponSniper()
            };
            static size_t p = 0;
            const size_t i = (p += 1) %= credits.size();
            const auto& transform = registry.get<Transform>(treasure);
            //gain Weapon
            registry.emplace_or_replace<Weapon>(gainer, Weapon{
                                                    .entity = credits.at(i)->build(transform.matrix),
                                                    .transform = {.offset = {0.3, -0.2}}
                                                });
        }
        break;
    case StatusTreasure::Carrot:
        {
            EventManager::getInstance().dispatcher.enqueue<AddBuff<BuffCarrot>>({gainer});
        }
        break;
    case StatusTreasure::Red:
        {
            EventManager::getInstance().dispatcher.enqueue<AddBuff<BuffRed>>({gainer});
        }
        break;
    case StatusTreasure::Blue:
        {
            EventManager::getInstance().dispatcher.enqueue<AddBuff<BuffSpeeding>>({gainer});
            EventManager::getInstance().dispatcher.enqueue<AddBuff<BuffHealing>>({gainer});
        }
        break;
    }
    registry.destroy(treasure);
}
