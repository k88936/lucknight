//
// Created by kvtoD on 6/30/2025.
//

#ifndef PHYSICSDESCIPTION_H
#define PHYSICSDESCIPTION_H
#include "../Type/Vector.h"


// 子弹标志（用于特殊处理）
struct PhysicsDes_Movement
{
    enum Type
    {
        Static, Dynamic, Kinematic
    };

    Type type = Type::Dynamic;
    bool isBullet = false;
    float linearDamping = 0.5f;
    bool rotationLocked = true;
    float gravityScale = 1;
    uint64_t contactCategoryBits = -1;
    uint64_t contactMaskBits = -1;
};

struct Material
{
    float density = 1.0f;
    float friction =0.0f;
};

// struct PhysicsDes_CircleShapeDesc {
//     float radius;
//     Material material;
// };

struct PhysicsDes_CapsuleShapeDesc
{
    float halfHeight;
    float radius;
    Material material;
};

struct PhysicsDes_CircleShapeDesc
{
    float radius;
    Material material;
};

struct PhysicsDes_BoxShapeDesc
{
    float halfWidth;
    float halfHeight;
    Material material;
};

#endif //PHYSICSDESCIPTION_H
