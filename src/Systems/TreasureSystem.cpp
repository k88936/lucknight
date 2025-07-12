//
// Created by root on 7/11/25.
//


#include <qvariant.h>

#include "TreasureSystem.h"
#include "../Components/Attachment.h"
#include "../Components/Transform.h"
#include "../Components/Types.h"
#include "../Core/World.h"
#include "../Events/GainEvents.h"
#include "../Managers/EventManager.h"
#include "../Prefab/PrefabWeapon.h"

TreasureSystem::TreasureSystem()
{
    EventManager::getInstance().dispatcher.sink<GainTreasure>().connect<&TreasureSystem::onGainTreasureEvent>(this);
}

TreasureSystem::~TreasureSystem()
{
    EventManager::getInstance().dispatcher.sink<GainTreasure>().disconnect(this);
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
    static std::vector<PrefabWeapon> credits = {PrefabWeapon(),};
    const size_t r = random() % credits.size();
    const auto& transform = registry.get<Transform>(treasure);
    registry.emplace_or_replace<Weapon>(gainer, Weapon{credits.at(r).build(transform.matrix)});
}
