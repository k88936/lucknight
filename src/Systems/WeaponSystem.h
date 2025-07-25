//
// Created by root on 7/9/25.
//

#ifndef WEAPONSYSTEM_H
#define WEAPONSYSTEM_H
#include "System.h"
#include "../Events/WeaponShootEvent.h"


class WeaponSystem : public System<WeaponSystem>
{
public:
    constexpr  static  int MAGIC_INFINITY_AMMO= -130724;
    void update() override;
    WeaponSystem();
    ~WeaponSystem() override;
    void onShootEvent(const WeaponShootEvent& event);
};


#endif //WEAPONSYSTEM_H
