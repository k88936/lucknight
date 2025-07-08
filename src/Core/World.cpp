//
// Created by kvtoD on 6/30/2025.
//

#include "World.h"

#include "../Prefab/PrefabPlatform.h"
#include "../Prefab/PrefabPlayer.h"
#include "../Prefab/PrefabProjectile.h"
#include "../Systems/AnimationSystem.h"
#include "../Systems/ScriptSystem.h"
#include "../Systems/KeyboardControlSystem.h"
#include "../Systems/PhysicsSystem.h"
#include "../Utils/Dumper.h"

void World::update()
{
    PhysicsSystem::getInstance().update();
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
    PrefabPlayer p;
    p.build(Matrix::fromTranslation({0, 4}));
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



    PrefabProjectile pp;
    auto  e =pp.build(Matrix::fromTranslation({0, 3}));
    EventManager::getInstance().dispatcher.enqueue<MoverEvent>(MoverEvent{.entity = e,.impulse = {3,0}});

    ScriptSystem::getInstance().init();
    AnimationSystem::getInstance().update();
}
