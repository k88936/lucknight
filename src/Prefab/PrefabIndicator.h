//
// Created by root on 7/12/25.
//

#ifndef PREFABINDICATOR_H
#define PREFABINDICATOR_H
#include "Prefab.h"


class PrefabIndicator : public Prefab
{
public:
    entt::entity build(const Matrix& transform) override;
};


#endif //PREFABINDICATOR_H
