//
// Created by kvtoD on 7/24/2025.
//

#ifndef BUFFBASE_H
#define BUFFBASE_H
#include "../Script.h"
#include "../../Systems/BuffSystem.h"
#define BUFF(className,seq)                                                                                             \
template<typename... Components>                                                                                        \
class AUX_CLASS(className) :public virtual BuffBase{                                                                    \
    DECLARE_COMPONENTS(seq)                                                                                             \
public:                                                                                                                 \
    static bool _register(){                                                                                            \
        BuffSystem::getInstance().registerBuff<Components...  >();                                                      \
        return true;                                                                                                    \
    }                                                                                                                   \
};                                                                                                                      \
class className :public AUX_CLASS(className)TEMPLATE_PARAM(className,seq)

// Base Buff class
class BuffBase
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

    virtual bool isExpired() const { return false; }
};

#endif //BUFFBASE_H
