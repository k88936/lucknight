//
// Created by kvtoD on 7/24/2025.
//

#include "BuffSystem.h"

BuffSystem::BuffSystem()
{
}

void BuffSystem::update()
{
    for (const auto& script : updateBuffs)
    {
        script();
    }

    for (const auto& script : eventBuffs)
    {
        script();
    }
}

BuffSystem::~BuffSystem()
{
}
