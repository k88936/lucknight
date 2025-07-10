//
// Created by root on 7/10/25.
//

#ifndef ATTACHMENTSYSTEM_H
#define ATTACHMENTSYSTEM_H
#include "System.h"
#include "../Components/Attachment.h"
#include "../Components/Transform.h"
#include "../Core/World.h"


class AttachmentSystem : System<AttachmentSystem>
{
    void update() override;
};

inline void AttachmentSystem::update()
{
    auto& registry = World::getInstance().registry;
    const auto view = registry.view<Transform,Weapon>();
    view.each([]()
    {

    }) ;
}


#endif //ATTACHMENTSYSTEM_H
