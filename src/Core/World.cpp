//
// Created by kvtoD on 6/30/2025.
//

#include "World.h"

#include "../Prefab/PrefabPlatform.h"
#include "../Prefab/PrefabPlayer.h"
#include "../Prefab/PrefabProjectile.h"
#include "../Prefab/PrefabTreasure.h"
#include "../Prefab/PrefabWeapon.h"
#include "../Systems/AnimationSystem.h"
#include "../Systems/AttachmentSystem.h"
#include "../Systems/ScriptSystem.h"
#include "../Systems/KeyboardControlSystem.h"
#include "../Systems/PhysicsSystem.h"
#include "../Systems/WeaponSystem.h"
#include "../Systems/TreasureSystem.h"
#include "../Utils/Dumper.h"

void World::update()
{
    const long currentTime = getCurrentTimeMilliseconds();
    deltaTime = static_cast<float>(currentTime - lastUpdateTime) / 1000.0f;
    assert(deltaTime<1);
    lastUpdateTime = currentTime;

    PhysicsSystem::getInstance().update();
    AttachmentSystem::getInstance().update();
    WeaponSystem::getInstance().update();
    TreasureSystem::getInstance().update();
    // Update input first
    KeyboardControlSystem::getInstance().update();

    // Update scripts (which now include state management)
    ScriptSystem::getInstance().update();

    AnimationSystem::getInstance().update();
    // dump<Transform>();
    // Update physics after scripts have updated forces/impulses
}

void World::init()
{
    lastUpdateTime = getCurrentTimeMilliseconds();

    PhysicsSystem::getInstance();
    PrefabPlayer p1;
    p1.keymap={Key::Key_A, Key::Key_D, Key::Key_W, Key::Key_S, Key::Key_F};
    p1.build(Matrix::fromTranslation({0, 4}));


    PrefabPlayer p2;
    p2.keymap={Key::Key_Left, Key::Key_Right, Key::Key_Up, Key::Key_Down, Key::Key_M};
    p2.build(Matrix::fromTranslation({2, 4}));

    PrefabPlatform pm;

    pm.build(Matrix::fromTranslation({0, 9}), 4);
    pm.build(Matrix::fromTranslation({0, 1}), 1);


    pm.build(Matrix::fromTranslation({-6, 6}), 0);
    pm.build(Matrix::fromTranslation({-5, 6}), 1);
    pm.build(Matrix::fromTranslation({-4, 6}), 0);
    pm.build(Matrix::fromTranslation({-3, 6}), 1);
    pm.build(Matrix::fromTranslation({3, 6}), 2);
    pm.build(Matrix::fromTranslation({4, 6}), 3);
    pm.build(Matrix::fromTranslation({5, 6}), 2);
    pm.build(Matrix::fromTranslation({6, 6}), 3);


    pm.build(Matrix::fromTranslation({-3, 0}), 0);
    pm.build(Matrix::fromTranslation({-2, 0}), 1);
    pm.build(Matrix::fromTranslation({-1, 0}), 2);
    pm.build(Matrix::fromTranslation({0, 0}), 3);
    pm.build(Matrix::fromTranslation({1, 0}), 4);
    pm.build(Matrix::fromTranslation({2, 0}), 1);
    pm.build(Matrix::fromTranslation({3, 0}), 2);

    pm.build(Matrix::fromTranslation({-9, -3}), 0);
    pm.build(Matrix::fromTranslation({-8, -3}), 1);
    pm.build(Matrix::fromTranslation({-7, -3}), 2);
    pm.build(Matrix::fromTranslation({-6, -3}), 0);
    pm.build(Matrix::fromTranslation({-5, -3}), 1);
    pm.build(Matrix::fromTranslation({-4, -3}), 2);
    pm.build(Matrix::fromTranslation({4, -3}), 4);
    pm.build(Matrix::fromTranslation({5, -3}), 1);
    pm.build(Matrix::fromTranslation({6, -3}), 2);
    pm.build(Matrix::fromTranslation({7, -3}), 4);
    pm.build(Matrix::fromTranslation({8, -3}), 1);
    pm.build(Matrix::fromTranslation({9, -3}), 2);


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
