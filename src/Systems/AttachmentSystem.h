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
    AttachmentSystem();
    ~AttachmentSystem() override;

    template <typename Attachment>
    void applyTransform();

    template <typename Attachment>
    void connectDestroyListener();
    template <typename Attachment>
    void disconnectDestroyListener();

    template <typename Attachment>
    static void onDestroy(entt::registry& registry, entt::entity entity);

    void update() override;
};

template <typename Attachment>
void AttachmentSystem::applyTransform()
{
    auto& registry = World::getInstance().registry;
    const auto view = registry.view<const Transform, Attachment>();

    for (auto entity : view)
    {
        const auto& fatherTransform = view.template get<const Transform>(entity);
        const auto& attachment = view.template get<Attachment>(entity);

        registry.replace<Transform>(attachment.entity,
            fatherTransform.matrix.mapMatrix(attachment.transform.offset, attachment.transform.followFlip));
    }
}

template <typename Attachment>
void AttachmentSystem::connectDestroyListener()
{
    auto& registry = World::getInstance().registry;
    registry.on_destroy<Attachment>().template connect<&AttachmentSystem::onDestroy<Attachment>>();
}

template <typename Attachment>
void AttachmentSystem::disconnectDestroyListener()
{
    auto& registry = World::getInstance().registry;
    registry.on_destroy<Attachment>().template disconnect<&AttachmentSystem::onDestroy<Attachment>>();
}

template <typename Attachment>
void AttachmentSystem::onDestroy(entt::registry& registry, entt::entity entity)
{
    const Attachment& attachment = registry.get<Attachment>(entity);
    registry.destroy(attachment.entity);
}
#endif //ATTACHMENTSYSTEM_H
