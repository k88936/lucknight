//
// Created by root on 7/9/25.
//

#include "PrefabWeapon.h"

#include "../Components/Drawable.h"
#include "../Components/Status.h"
#include "../Core/World.h"
#include "PrefabProjectile.h"
#include "../Events/BodyEvents.h"
#include "../Managers/EventManager.h"
#include "../Managers/TextureManager.h"

struct Texture;

entt::entity PrefabWeapon::build(const Matrix& transform)
{
    auto& registry = World::getInstance().registry;

    const auto entity = Prefab::build(transform);


    Texture* texture = TextureManager::getInstance().getTextures("assets/weapon/", 0, {.scale = 0.4});
    registry.emplace<Drawable>(entity, Drawable{.texture = texture});

    static PrefabProjectile* projectile = []
    {
        const auto p = new PrefabProjectile();
        p->density = 4;
        return p;
    }();
    registry.emplace<StatusWeapon>(entity, StatusWeapon{
                                       .ammoLeft = 5, .accuracy = 1, .delay = 3, .ammoType = projectile
                                   });
    return entity;
}
