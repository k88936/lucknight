//
// Created by root on 7/5/25.
//

#ifndef SCRIPTSYSTEM_H
#define SCRIPTSYSTEM_H
#include "System.h"
#include "../Core/World.h"

class ScriptSystem final : public System<ScriptSystem>
{
    std::vector<std::function<void()>> updateScripts;

public:
    template <typename... S>
    void registerScript();
    template <class S>
    static void scriptConstructCallback(entt::entity entity);
    // template <typename S>
    // void scriptConstructCallback(entt::entity entity);
    void update() override;
    ScriptSystem();
    ~ScriptSystem() override;
};

template <typename... S>
void ScriptSystem::registerScript()
{
    using ScriptType = std::tuple_element_t<0, std::tuple<S...>>;
    auto& registry = World::getInstance().registry;
    // registry.on_construct<ScriptType>().template connect<&ScriptSystem::scriptConstructCallback<ScriptType>>(this);
    //TODO Script cant be add dynamically by now
    updateScripts.emplace_back([]
    {
        auto& registry = World::getInstance().registry;
        for (const auto view = registry.view<S...>(); const auto entity : view)
        {
            registry.get<ScriptType>(entity).aux_update(entity);
        }
    });
    registry.on_construct<ScriptType>().template connect<&ScriptSystem::scriptConstructCallback<ScriptType>>();
}

template <typename S>
void ScriptSystem::scriptConstructCallback(const entt::entity entity)
{
    auto& registry = World::getInstance().registry;
    assert(registry.valid(entity));
    registry.get<S>(entity).aux_init(entity);
}

#endif //SCRIPTSYSTEM_H
