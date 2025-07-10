//
// Created by root on 7/9/25.
//

#ifndef PREFABWEAPON_H
#define PREFABWEAPON_H
#include "Prefab.h"


class PrefabWeapon : Prefab
{
public:
    entt::entity build(const Matrix& transform = Matrix()) override;
};


#endif //PREFABWEAPON_H
