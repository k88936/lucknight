//
// Created by root on 7/7/25.
//

#ifndef PREFABPROJECTILE_H
#define PREFABPROJECTILE_H
#include "Prefab.h"


class PrefabProjectile : Prefab
{
public:
    entt::entity build(const Matrix& transform) override;
};


#endif //PREFABPROJECTILE_H
