//
// Created by root on 7/7/25.
//

#ifndef PROJECTILESCRIPT_H
#define PROJECTILESCRIPT_H
#include "Script.h"
#include "../Components/Status.h"


SCRIPT(ProjectileScript, (StatusProjectile))
{
    void update() override;
    void init() override;
};


#endif //PROJECTILESCRIPT_H
