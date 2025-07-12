//
// Created by root on 7/10/25.
//

#include "AttachmentSystem.h"

void AttachmentSystem::update()
{
    auto& registry = World::getInstance().registry;
    const auto weaponHoldersView = registry.view<const Transform, Weapon>();

    for (const auto [holderEntity, holderTransform, weapon] : weaponHoldersView.each())
    {
        registry.replace<Transform>(weapon.weaponEntity,
                                    holderTransform.matrix.mapMatrix(weapon.transform.offset, weapon.transform.flip));
    }
}
