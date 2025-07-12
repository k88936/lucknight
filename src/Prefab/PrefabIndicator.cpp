//
// Created by root on 7/12/25.
//

#include "PrefabIndicator.h"

#include "../Core/World.h"

entt::entity PrefabIndicator::build(const Matrix& transform)
{
    auto & registry =  World::getInstance().registry;
    const auto entity =Prefab::build(transform);


}
