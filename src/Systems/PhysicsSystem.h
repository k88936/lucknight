//
// Created by root on 7/3/25.
//

#ifndef PHYSICSSYSTEM_H
#define PHYSICSSYSTEM_H
#include "System.h"
#include "TaskScheduler_c.h"
#include "../Components/Body.h"
#include "../Components/SpaceQuery.h"
#include "../Components/Transform.h"
#include "../Core/World.h"
#include "../Events/BodyEvents.h"
#include "../Events/GainEvents.h"
#include "../Events/MoverEvents.h"
#include "../Managers/EventManager.h"
#include "../Prefab/PrefabWeapon.h"
#include "../Utils/Wrapper.h"
#include "box2d/box2d.h"
#include "box2d/types.h"


class PhysicsSystem final : public System<PhysicsSystem>
{
public:
    b2WorldId worldId{};
    constexpr static int e_maxTasks = 128;
    enkiTaskScheduler* scheduler;
    enkiTaskSet* tasks[e_maxTasks]{};

    typedef struct TaskData
    {
        b2TaskCallback* box2dTask;
        void* box2dContext;
    } TaskData;

    TaskData taskData[e_maxTasks]{};
    int taskCount = 0;


    PhysicsSystem();
    ~PhysicsSystem() override;
    void applyEffect();
    void syncData();
    void destroyBody(entt::entity entity);
    template <typename Detector>
    bool static updateDetector_aux(b2ShapeId shapeId, void* context);
    template <typename Detector>
    void updateDetector();
    void detectProjectileHit();
    void update() override;;
    void createBody(entt::entity entity);
    void step() const;
    void moveMover(const MoverEvent& event);
    static void ExecuteRangeTask(uint32_t start, uint32_t end, uint32_t threadIndex, void* context);
    static void* EnqueueTask(b2TaskCallback* box2dTask, int itemCount, int minRange, void* box2dContext,
                             void* userContext);
    static void FinishTask(void* userTask, void* userContext);
    void* EnqueueTaskImpl(b2TaskCallback* box2dTask, int itemCount, int minRange, void* box2dContext);
    void FinishTaskImpl(void* userTask) const;
};

template <typename Detector>
inline bool PhysicsSystem::updateDetector_aux(b2ShapeId shapeId, void* context)
{
    auto& registry = World::getInstance().registry;
    registry.patch<Detector>(EntityWrapper(context), [](Detector& detector)
    {
        detector.got = true;
    });
    return false;
}

template <>
inline bool PhysicsSystem::updateDetector_aux<TreasureDetector>(b2ShapeId shapeId, void* context)
{
    static PrefabWeapon pw;
    EventManager::getInstance().dispatcher.enqueue<GainTreasure>({
        EntityWrapper(context),
        pw.build()
    });
    auto& registry = World::getInstance().registry;
    registry.patch<TreasureDetector>(EntityWrapper(context), [](TreasureDetector& detector)
    {
        detector.got = true;
    });

    registry.destroy(EntityWrapper(EntityWrapper(b2Shape_GetUserData(shapeId))));
    return false;
}

template <typename Detector>
inline void PhysicsSystem::updateDetector()
{
    auto& registry = World::getInstance().registry;
    const auto view = registry.view<Body, Transform, Detector>();
    view.each([&](const entt::entity entity, const Body& body, const Transform& transform, Detector& detector)
    {
        detector.got = false;
        const b2Circle circle = {b2TransformPoint(transform.matrix, detector.offset), detector.radius};
        const b2ShapeProxy proxy = b2MakeProxy(&circle.center, 1, circle.radius);
        const b2QueryFilter filter = {.categoryBits = Detector::category(), .maskBits = Detector::mask()};
        b2World_OverlapShape(worldId, &proxy, filter, &PhysicsSystem::updateDetector_aux<Detector>,
                             EntityWrapper(entity));
    });
}

#endif //PHYSICSSYSTEM_H
