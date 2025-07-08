//
// Created by root on 7/3/25.
//

#ifndef PHYSICSSYSTEM_H
#define PHYSICSSYSTEM_H
#include "System.h"
#include "TaskScheduler_c.h"
#include "../Components/Transform.h"
#include "../Events/MoverEvents.h"
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


    static bool preSolve(b2ShapeId shapeIdA, b2ShapeId shapeIdB, b2Vec2 point, b2Vec2 normal, void* context);
    PhysicsSystem();
    ~PhysicsSystem() override;
    void initWorld(b2WorldId worldId);
    void applyEffect();
    void syncData();
    void destroyBody();
    bool static updateGroundDetectors_aux(b2ShapeId shapeId, void* context);
    void updateGroundDetectors();
    void detectProjectileHit();
    void update() override;;
    void createBody() const;
    void step() const;
    void moveMover(const MoverEvent& event);
    static void ExecuteRangeTask(uint32_t start, uint32_t end, uint32_t threadIndex, void* context);
    static void* EnqueueTask(b2TaskCallback* box2dTask, int itemCount, int minRange, void* box2dContext,
                             void* userContext);
    static void FinishTask(void* userTask, void* userContext);
    void* EnqueueTaskImpl(b2TaskCallback* box2dTask, int itemCount, int minRange, void* box2dContext);
    void FinishTaskImpl(void* userTask) const;
};


#endif //PHYSICSSYSTEM_H
