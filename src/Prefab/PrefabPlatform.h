//
// Created by root on 7/6/25.
//

#ifndef PREFABPLATFORM_H
#define PREFABPLATFORM_H
#include "Prefab.h"


class PrefabPlatform : public Prefab{
protected:
    entt::entity build(const Matrix& transform) override;
public:
    entt::entity build(const Matrix& transform,int imageIndex);
};



#endif //PREFABPLATFORM_H
