//
// Created by root on 7/10/25.
//

#ifndef PREFABTREASURE_H
#define PREFABTREASURE_H
#include "Prefab.h"


class PrefabTreasure :Prefab {
public:

   entt::entity build(const Matrix& transform) override;

};



#endif //PREFABTREASURE_H
