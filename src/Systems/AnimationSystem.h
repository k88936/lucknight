//
// Created on 7/4/25.
//

#ifndef ANIMATORSYSTEM_H
#define ANIMATORSYSTEM_H

#include "System.h"
#include "../Managers/EventManager.h"
#include "../Core/World.h"
#include "../Components/Animator.h"
#include "../Events/AnimationChangeEvent.h"
#include <string>

#include "../Components/Drawable.h"

class AnimationSystem final : public System<AnimationSystem>
{
public:
    AnimationSystem();
    virtual ~AnimationSystem() override;
    void update() override;

    // Register a state-based animation
    template <typename State>
    void registerAnimation(const entt::entity entity, const std::string& basePath,const Texture::Config& textureConfig, const Clip& clipConfig=Clip())
    {
        constexpr auto stateId = entt::type_hash<State>::value();
        registerAnimation_aux(entity, basePath, stateId,textureConfig, clipConfig);
    }


    // Play a specific animation by name
    template <typename State>
    void play(const entt::entity entity)
    {
        constexpr auto stateId = entt::type_hash<State>::value();
        EventManager::getInstance().dispatcher.enqueue<AnimationChangeEvent>(entity, stateId);
    }

    void onChange(const AnimationChangeEvent&);

private:
    void registerAnimation_aux(entt::entity entity, const std::string& basePath, entt::id_type stateId,
                               const Texture::Config& textureConfig, const Clip& clipConfig);
    // Update animation based on elapsed time
    void updateAnimation(entt::entity entity, Animator& anim, float deltaTime);

    // Update the drawable component with the current frame
    void updateDrawableTexture(::entt::entity entity, const ::Animator& anim, Drawable& drawable);
    // Last update time for calculating deltaTime
    long lastUpdateTime = 0;
};


#endif //ANIMATORSYSTEM_H
