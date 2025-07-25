//
// Created by kvtoD on 7/25/2025.
//

#ifndef EXPIREDMIXIN_H
#define EXPIREDMIXIN_H
#include <variant>

#include "entt/entity/view.hpp"

struct ExpiredMixin
{
    virtual ~ExpiredMixin() = default;
    virtual void reset(){};

    virtual bool isExpired() const =0;
};
#endif //EXPIREDMIXIN_H
