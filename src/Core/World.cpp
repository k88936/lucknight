//
// Created by kvtoD on 6/30/2025.
//

#include "World.h"

#include "../Events/LifeEvents.h"
#include "../Prefab/PrefabPlatform.h"
#include "../Prefab/PrefabPlayer.h"
#include "../Prefab/PrefabProjectile.h"
#include "../Prefab/PrefabTreasure.h"
#include "../Prefab/PrefabWeapon.h"
#include "../Systems/AnimationSystem.h"
#include "../Systems/AttachmentSystem.h"
#include "../Systems/BuffSystem.h"
#include "../Systems/HealthSystem.h"
#include "../Systems/ScriptSystem.h"
#include "../Systems/KeyboardControlSystem.h"
#include "../Systems/PhysicsSystem.h"
#include "../Systems/WeaponSystem.h"
#include "../Systems/TreasureSystem.h"
#include "../Utils/Dumper.h"

World::World()
{
    EventManager::getInstance().dispatcher.sink<DeathPlayer>().connect<&World::onPlayerDeath>(this);
}

World::~World()
{
    EventManager::getInstance().dispatcher.sink<DeathPlayer>().disconnect();
}

void World::onPlayerDeath()
{
    playerDeathCallback();
}

void World::update()
{
    const long currentTime = getCurrentTimeMilliseconds();
    deltaTime = static_cast<float>(currentTime - lastUpdateTime) / 1000.0f;
    assert(deltaTime<100);
    lastUpdateTime = currentTime;

    PhysicsSystem::getInstance().update();
    AttachmentSystem::getInstance().update();
    WeaponSystem::getInstance().update();
    HealthSystem::getInstance().update();
    TreasureSystem::getInstance().update();
    // Update input first
    KeyboardControlSystem::getInstance().update();

    // Update scripts (which now include state management)
    ScriptSystem::getInstance().update();
    BuffSystem::getInstance().update();

    AnimationSystem::getInstance().update();
    // dump<Transform>();
    // Update physics after scripts have updated forces/impulses
}

void World::init()
{
    lastUpdateTime = getCurrentTimeMilliseconds();

    PhysicsSystem::getInstance();
    PrefabPlayer p1;
    p1.keymap = {Key::Key_A, Key::Key_D, Key::Key_W, Key::Key_S, Key::Key_F};
    p1.build(Matrix::fromTranslation({0, 4}));


    PrefabPlayer p2;
    p2.keymap = {Key::Key_Left, Key::Key_Right, Key::Key_Up, Key::Key_Down, Key::Key_M};
    p2.build(Matrix::fromTranslation({2, 4}));

    PrefabPlatformSoil soil;
    PrefabPlatformGrass grass;
    PrefabPlatformSnow snow;

    soil.build(Matrix::fromTranslation({0, 9}));
    soil.build(Matrix::fromTranslation({0, 1}));


    soil.build(Matrix::fromTranslation({-6, 6}));
    soil.build(Matrix::fromTranslation({-5, 6}));
    grass.build(Matrix::fromTranslation({-4, 6}));
    grass.build(Matrix::fromTranslation({-3, 6}));
    soil.build(Matrix::fromTranslation({3, 6}));
    soil.build(Matrix::fromTranslation({4, 6}));
    soil.build(Matrix::fromTranslation({5, 6}));
    soil.build(Matrix::fromTranslation({6, 6}));


    grass.build(Matrix::fromTranslation({-3, 0}));
    snow.build(Matrix::fromTranslation({-2, 0}));
    soil.build(Matrix::fromTranslation({2, 0}));
    snow.build(Matrix::fromTranslation({3, 0}));
    soil.build(Matrix::fromTranslation({4, 0}));

    soil.build(Matrix::fromTranslation({-9, -3}));
    soil.build(Matrix::fromTranslation({-8, -3}));
    soil.build(Matrix::fromTranslation({-7, -3}));
    soil.build(Matrix::fromTranslation({-6, -3}));
    snow.build(Matrix::fromTranslation({-5, -3}));
    snow.build(Matrix::fromTranslation({-4, -3}));
    soil.build(Matrix::fromTranslation({4, -3}));
    soil.build(Matrix::fromTranslation({5, -3}));
    soil.build(Matrix::fromTranslation({6, -3}));
    soil.build(Matrix::fromTranslation({7, -3}));
    soil.build(Matrix::fromTranslation({8, -3}));
    soil.build(Matrix::fromTranslation({9, -3}));


    // PrefabProjectile pp;
    // auto  e =pp.build(Matrix::fromTranslation({0, 3}));
    // EventManager::getInstance().dispatcher.enqueue<MoverEvent>(MoverEvent{.entity = e,.impulse = {3,0}});
    PrefabTreasure pt;
    pt.build(Matrix::fromTranslation({3, 10}));
    pt.build(Matrix::fromTranslation({3, 4}));

    ScriptSystem::getInstance().init();
    AnimationSystem::getInstance().update();
}

long World::getCurrentTimeMilliseconds()
{
    const auto now = std::chrono::high_resolution_clock::now();
    const auto duration = now.time_since_epoch();
    const long millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    return millis;
}
