//
// Created by root on 7/12/25.
//

#ifndef PREFABINDICATOR_H
#define PREFABINDICATOR_H
#include "Prefab.h"
#include "Texture.h"


class PrefabIndicator : public Prefab
{
public:
    entt::entity build(const Matrix& transform) override;
    std::vector<const Texture*> textures;
};


#endif //PREFABINDICATOR_H
