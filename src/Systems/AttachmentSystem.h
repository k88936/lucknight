//
// Created by root on 7/10/25.
//

#ifndef ATTACHMENTSYSTEM_H
#define ATTACHMENTSYSTEM_H
#include "System.h"
#include "../Components/Transform.h"
#include "../Core/World.h"


class AttachmentSystem : public System<AttachmentSystem>
{
public:
    template <typename Attachment>
    void applyTransform();
    void update() override;
};

template <typename Attachment>
 void AttachmentSystem::applyTransform()
{
    auto& registry = World::getInstance().registry;
    const auto view = registry.view<const Transform, Attachment>();

    for (const auto [father, fatherTransform, child] : view.each())
    {
        registry.replace<Transform>(child.entity,
                                    fatherTransform.matrix.mapMatrix(child.transform.offset, child.transform.flip));
    }
}


#endif //ATTACHMENTSYSTEM_H
