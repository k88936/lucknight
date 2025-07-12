//
// Created by root on 7/12/25.
//

#include "PrefabIndicator.h"

#include "../Components/Drawable.h"
#include "../Core/World.h"
#include "../Managers/TextureManager.h"
#include "../Scripts/IndicatorScript.h"

entt::entity PrefabIndicator::build(const Matrix& transform)
{
    auto& registry = World::getInstance().registry;
    const auto entity = Prefab::build(transform);
    registry.emplace<Drawable>(entity);
    IndicatorScript script;
    script.frames= textures;
    registry.emplace<IndicatorScript>(entity, script);
    return entity;
}
