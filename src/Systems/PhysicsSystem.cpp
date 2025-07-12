//
// Created by root on 7/3/25.
//

#include "PhysicsSystem.h"
#include "../Components/SpaceQuery.h"
#include "../Components/Types.h"
#include "../Events/MoverEvents.h"
#include "../Events/ProjectileHitEvent.h"
#include "../Managers/EventManager.h"
#include "../Utils/Wrapper.h"
#include "../Core/World.h"
#include "../Components/Body.h"
#include "../Components/PhysicsDesciption.h"
#include "../Utils/Wrapper.h"
#include "../Components/Tags.h"
#include "../Events/BodyEvents.h"
#include "../Type/Errors.h"

void PhysicsSystem::moveMover(const MoverEvent& event)
{
    auto& registry = World::getInstance().registry;
    const auto entity = event.entity;
    assert(registry.valid(entity));
    assert(registry.all_of<Body>(entity));
    const auto& body = registry.get<Body>(entity);
    auto& bodyId = body.bodyID;
    b2Body_ApplyForceToCenter(bodyId, event.force, true);
    b2Body_ApplyLinearImpulseToCenter(bodyId, event.impulse, true);
}

PhysicsSystem::PhysicsSystem()
{
    // EventManager::getInstance().dispatcher.sink<BodyCreation>().connect<&PhysicsSystem::createBody>(this);
    // EventManager::getInstance().dispatcher.sink<BodyDestruction>().connect<&PhysicsSystem::destroyBody>(this);
    auto& registry = World::getInstance().registry;
    registry.on_construct<Body>().connect<&PhysicsSystem::createBody>(this);
    registry.on_destroy<Body>().connect<&PhysicsSystem::destroyBody>(this);
    EventManager::getInstance().dispatcher.sink<MoverEvent>().connect<&PhysicsSystem::moveMover>(this);


    constexpr int workerCount = 4;
    scheduler = enkiNewTaskScheduler();
    struct enkiTaskSchedulerConfig config = enkiGetTaskSchedulerConfig(scheduler);
    config.numTaskThreadsToCreate = workerCount - 1;
    enkiInitTaskSchedulerWithConfig(scheduler, config);
    for (auto& task : tasks)
    {
        task = enkiCreateTaskSet(scheduler, ExecuteRangeTask);
    }
    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.userTaskContext = this;
    worldDef.enqueueTask = &PhysicsSystem::EnqueueTask;
    worldDef.finishTask = &PhysicsSystem::FinishTask;
    worldDef.workerCount = workerCount;
    worldId = b2CreateWorld(&worldDef);
}


void PhysicsSystem::applyEffect()
{
    EventManager::getInstance().dispatcher.update<MoverEvent>();
}

void PhysicsSystem::syncData()
{
    auto& registry = World::getInstance().registry;
    const auto view = registry.view<const
                                    Body, Transform>();

    view.each([](const entt::entity& entity, const Body& body, Transform& transform)
    {
        auto& bodyId = body.bodyID;
        transform.matrix.updateTransform(b2Body_GetTransform(bodyId));
        // transform.matrix = Matrix(b2Body_GetTransform(bodyId));
    });
}

void PhysicsSystem::destroyBody(const entt::entity entity)
{
    auto& registry = World::getInstance().registry;
    assert(registry.valid(entity));
    assert(registry.all_of<Body>(entity));
    const auto& body = registry.get<Body>(entity);
    b2DestroyBody(body.bodyID);
}


void PhysicsSystem::detectProjectileHit()
{
    auto& registry = World::getInstance().registry;
    const auto view = registry.view<const Body, const TypeProjectile>();
    view.each([](const Body& body)
    {
        constexpr size_t maxContactCount = 4;
        b2ContactData contactData[maxContactCount];
        const size_t count = b2Body_GetContactData(body.bodyID, contactData, maxContactCount);
        for (size_t i = 0; i < count; i++)
        {
            const auto& contact = contactData[i];
            const auto& shapeA = contact.shapeIdA;
            const auto& shapeB = contact.shapeIdB;
            entt::entity projectile;
            entt::entity target;
            if (b2Shape_GetFilter(shapeA).categoryBits == TypeProjectile::category() &&
                b2Shape_GetFilter(shapeB).categoryBits == TypePlayer::category())
            {
                projectile = EntityWrapper(b2Shape_GetUserData(shapeA));
                target = EntityWrapper(b2Shape_GetUserData(shapeB));
            }
            else if (b2Shape_GetFilter(shapeA).categoryBits == TypePlayer::category() &&
                b2Shape_GetFilter(shapeB).categoryBits == TypeProjectile::category())
            {
                projectile = EntityWrapper(b2Shape_GetUserData(shapeB));
                target = EntityWrapper(b2Shape_GetUserData(shapeA));
            }
            else
            {
                continue;
            }
            EventManager::getInstance().dispatcher.enqueue<ProjectileHitEvent>(
                ProjectileHitEvent{
                    .projectile = projectile, .target = target
                });
        }
    });
}

void PhysicsSystem::update()
{
    updateDetector<GroundDetector>();
    updateDetector<TreasureDetector>();
    applyEffect();
    step();
    syncData();
    detectProjectileHit();
}

void PhysicsSystem::createBody(const entt::entity entity)
{
    auto& registry = World::getInstance().registry;

    assert(registry.valid(entity));
    assert(registry.all_of<Transform>(entity));
    assert(registry.all_of<PhysicsDes_Movement>(entity));
    b2BodyDef bodyDef = b2DefaultBodyDef();
    b2ShapeDef shapeDef = b2DefaultShapeDef();
    const auto& movementDesc = registry.try_get<PhysicsDes_Movement>(entity);
    const auto& transform = registry.get<Transform>(entity);

    switch (movementDesc->type)
    {
    case PhysicsDes_Movement::Dynamic:
        bodyDef.type = b2_dynamicBody;
        break;
    case PhysicsDes_Movement::Static:
        bodyDef.type = b2_staticBody;
        break;
    case PhysicsDes_Movement::Kinematic:
        bodyDef.type = b2_kinematicBody;
        break;
    }
    bodyDef.isBullet = movementDesc->isBullet;
    bodyDef.linearDamping = movementDesc->linearDamping;
    bodyDef.motionLocks.angularZ = movementDesc->rotationLocked;
    bodyDef.position = transform.matrix.getPosition();
    bodyDef.rotation = transform.matrix.getRotation();
    bodyDef.userData = EntityWrapper(entity);
    bodyDef.gravityScale = movementDesc->gravityScale;
    shapeDef.filter = {
        .categoryBits = movementDesc->contactCategoryBits, .maskBits = movementDesc->contactMaskBits
    };
    const b2BodyId bodyId = b2CreateBody(worldId, &bodyDef);
    shapeDef.userData = EntityWrapper(entity);
    shapeDef.enablePreSolveEvents = true;
    b2ShapeId shapeId;
    if (const auto& capsuleDesc = registry.try_get<PhysicsDes_CapsuleShapeDesc>(entity))
    {
        shapeDef.material.friction = capsuleDesc->material.friction;
        const b2Capsule shape = {
            .center1 = {0, capsuleDesc->halfHeight - capsuleDesc->radius},
            .center2 = {0, -(capsuleDesc->halfHeight - capsuleDesc->radius)},
            .radius = capsuleDesc->radius
        };
        shapeId = b2CreateCapsuleShape(bodyId, &shapeDef, &shape);
    }
    else if (const auto& boxDesc = registry.try_get<PhysicsDes_BoxShapeDesc>(entity))
    {
        shapeDef.material.friction = boxDesc->material.friction;
        const b2Polygon shape = b2MakeBox(boxDesc->halfWidth, boxDesc->halfHeight);

        shapeId = b2CreatePolygonShape(bodyId, &shapeDef, &shape);
    }
    else if (const auto& circleDesc = registry.try_get<PhysicsDes_CircleShapeDesc>(entity))
    {
        shapeDef.material.friction = circleDesc->material.friction;
        const b2Circle shape = {.radius = circleDesc->radius};
        shapeId = b2CreateCircleShape(bodyId, &shapeDef, &shape);
    }
    else
    {
        throw ComponentNotFoundException("Shape Desc component not found");
    }

    registry.patch<Body>(entity,

                         [&bodyId, &shapeId](Body& body)
                         {
                             body.bodyID = bodyId;
                             body.shapeID = shapeId;
                         }
    );
}

void PhysicsSystem::step() const
{
    constexpr int subStepCount = 4;
    b2World_Step(worldId, World::getInstance().getFixedDeltaTime(), subStepCount);

    // b2ContactData contactData = {};
    // int contactCount = b2Body_GetContactData(m_movingPlatformId, &contactData, 1);

    // if (m_context->hertz > 0.0f) {
    //     m_jumpDelay = b2MaxFloat(0.0f, m_jumpDelay - 1.0f / m_context->hertz);
    // }
}

PhysicsSystem::~PhysicsSystem()
{
    auto& registry = World::getInstance().registry;
    // EventManager::getInstance().dispatcher.sink<BodyCreation>().disconnect(this);
    // EventManager::getInstance().dispatcher.sink<BodyDestruction>().disconnect(this);
    registry.on_construct<Body>().disconnect(this);
    registry.on_destroy<Body>().disconnect(this);
    EventManager::getInstance().dispatcher.sink<MoverEvent>().disconnect(this);

    b2DestroyWorld(worldId);
    for (const auto& task : tasks)
    {
        enkiDeleteTaskSet(scheduler, task);
    }
    enkiDeleteTaskScheduler(scheduler);
}

void PhysicsSystem::ExecuteRangeTask(const uint32_t start, const uint32_t end, const uint32_t threadIndex,
                                     void* context)
{
    const auto data = static_cast<TaskData*>(context);
    data->box2dTask(start, end, threadIndex, data->box2dContext);
}

void* PhysicsSystem::EnqueueTask(b2TaskCallback* box2dTask, int itemCount, int minRange, void* box2dContext,
                                 void* userContext)
{
    return static_cast<PhysicsSystem*>(userContext)->EnqueueTaskImpl(box2dTask, itemCount, minRange, box2dContext);
}

void PhysicsSystem::FinishTask(void* userTask, void* userContext)
{
    static_cast<PhysicsSystem*>(userContext)->FinishTaskImpl(userTask);
}

void* PhysicsSystem::EnqueueTaskImpl(b2TaskCallback* box2dTask, int itemCount, int minRange, void* box2dContext)
{
    if (taskCount < e_maxTasks)
    {
        enkiTaskSet* task = tasks[taskCount];
        TaskData* data = taskData + taskCount;
        data->box2dTask = box2dTask;
        data->box2dContext = box2dContext;

        enkiParamsTaskSet params{};
        params.minRange = minRange;
        params.setSize = itemCount;
        params.pArgs = data;
        params.priority = 0;

        enkiSetParamsTaskSet(task, params);
        enkiAddTaskSet(scheduler, task);

        ++taskCount;

        return task;
    }

    box2dTask(0, itemCount, 0, box2dContext);
    return nullptr;
}

void PhysicsSystem::FinishTaskImpl(void* userTask) const
{
    const auto task = static_cast<enkiTaskSet*>(userTask);
    enkiWaitForTaskSet(scheduler, task);
}
