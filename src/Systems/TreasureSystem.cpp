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
#include "../Prefab/PrefabTreasure.h"
#include "../Scripts/Buff/Buffs.h"


TreasureSystem::TreasureSystem()
    : rng(std::random_device{}()),
      posDistX(-10.0f, 10.0f), // Example world bounds, adjust as needed
      posDistY(3, 10.0f),
      intervalDist(2.0f, 6.0f), // Random interval between 2 and 6 seconds
      treasureTypeDist(0, 3), // 4 types: Weapon, Carrot, Red, Blue
      lastUpdate(std::chrono::steady_clock::now())
{
    EventManager::getInstance().dispatcher.sink<GainTreasure>().connect<&TreasureSystem::onGainTreasureEvent>(this);
    spawnInterval = intervalDist(rng);
}

TreasureSystem::~TreasureSystem()
{
    EventManager::getInstance().dispatcher.sink<GainTreasure>().disconnect<&TreasureSystem::onGainTreasureEvent>(this);
}

void TreasureSystem::update()
{
    using namespace std::chrono;
    auto now = steady_clock::now();
    float delta = duration<float>(now - lastUpdate).count();
    lastUpdate = now;
    spawnTimer += delta;
    if (spawnTimer >= spawnInterval)
    {
        spawnRandomTreasure();
        spawnTimer = 0.0f;
        spawnInterval = intervalDist(rng);
    }
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
            EventManager::getInstance().dispatcher.enqueue<AddBuff<BuffSpeeding>>({gainer, {3.0f}});
            EventManager::getInstance().dispatcher.enqueue<AddBuff<BuffHealing>>({gainer});
        }
        break;
    }
    registry.destroy(treasure);
}

void TreasureSystem::spawnRandomTreasure()
{
    auto& registry = World::getInstance().registry;
    float x = posDistX(rng);
    float y = posDistY(rng);
    Matrix transform;
    int type = treasureTypeDist(rng);
    PrefabTreasure* prefab = nullptr;
    switch (type)
    {
    case 0: prefab = new PrefabTreasureWeapon();
        break;
    case 1: prefab = new PrefabTreasureCarrot();
        break;
    case 2: prefab = new PrefabTreasureRed();
        break;
    case 3: prefab = new PrefabTreasureBlue();
        break;
    }
    if (prefab)
    {
        prefab->build(Matrix::fromTranslation({x, y}));
        delete prefab;
    }
}
