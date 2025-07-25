//
// Created by kvtoD on 7/24/2025.
//

#ifndef BUFFBASE_H
#define BUFFBASE_H
#include "../Script.h"
#include "../../Systems/BuffSystem.h"
#define BUFF(className,seq)                                                                                             \
template<typename... Components>                                                                                        \
struct  AUX_CLASS(className) :public BuffBase ,Registerable<AUX_CLASS(className)<Components... >>{                                                                    \
    DECLARE_COMPONENTS(seq)                                                                                             \
public:                                                                                                                 \
    static bool _register(){                                                                                            \
        BuffSystem::getInstance().registerBuff<Components...  >();                                                      \
        return true;                                                                                                    \
    }                                                                                                                   \
};                                                                                                                      \
struct className :public AUX_CLASS(className)TEMPLATE_PARAM(className,seq)

// Base Buff class
struct BuffBase
{
public:
    BuffBase() = default;

    entt::entity entity{};
    virtual void bindComponents(entt::entity entity) =0;
    virtual ~BuffBase() = default;

    void aux_update(const entt::entity entity)
    {
        // this->entity = entity;
        // bindComponents(entity);
        onUpdate();
    }

    void aux_enter(const entt::entity entity)
    {
        this->entity = entity;
        bindComponents(entity);
        onEnter();
    }

    void aux_exit(const entt::entity entity)
    {
        onExit();
    }

    virtual void onEnter()
    {
    }

    virtual void onUpdate()
    {
    }

    virtual void onExit()
    {
    }
};

#endif //BUFFBASE_H
