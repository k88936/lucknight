//
// Created by root on 7/6/25.
//

#ifndef PREFABPLATFORM_H
#define PREFABPLATFORM_H
#include "Prefab.h"


class PrefabPlatform : public Prefab
{
public:
    float halfLen = 0.5f;
    entt::entity build(const Matrix& transform) override;
};

class PrefabPlatformGrass : public PrefabPlatform
{
public:
    entt::entity build(const Matrix& transform) override;
};

class PrefabPlatformSoil : public PrefabPlatform
{
    public:
    entt::entity build(const Matrix& transform) override;
};

class PrefabPlatformSnow : public PrefabPlatform
{
    public:
    entt::entity build(const Matrix& transform) override;
};
#endif //PREFABPLATFORM_H
