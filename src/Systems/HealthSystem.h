//
// Created by root on 7/7/25.
//

#ifndef HEALTHSYSTEM_H
#define HEALTHSYSTEM_H
#include "System.h"
#include "../Core/World.h"
#include "../Events/ProjectileHitEvent.h"


class HealthSystem final : public System<HealthSystem>
{
public:
    HealthSystem();
    ~HealthSystem() override;

    void onHit(const ProjectileHitEvent& event);
    void update() override;
};
#endif //HEALTHSYSTEM_H
