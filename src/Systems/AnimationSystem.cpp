//
// Created on 7/4/25.
//

#include "AnimationSystem.h"
#include "../Managers/TextureManager.h"
#include  "../Managers/EventManager.h"
#include "../Components/Drawable.h"
#include "../Utils/FileUtils.h"
#include <chrono>
#include <QDebug>
#include <cmath>

#include "../Events/AnimationChangeEvent.h"
#include "../Type/Errors.h"



AnimationSystem::AnimationSystem()
{
    EventManager::getInstance().dispatcher.sink<AnimationChangeEvent>().connect<&AnimationSystem::onChange>(this);
}

AnimationSystem::~AnimationSystem()
{
    EventManager::getInstance().dispatcher.sink<AnimationChangeEvent>().disconnect<&AnimationSystem::onChange>(this);
}

void AnimationSystem::update()
{
    EventManager::getInstance().dispatcher.update<AnimationChangeEvent>();
    // Calculate delta time
    auto& registry = World::getInstance().registry;
    const auto view = registry.view<Animator, Drawable>();
    for (auto [entity, anim, drawable] : view.each())
    {
        // Update animation frame
        updateAnimation(entity, anim, World::getInstance().getFrameDeltaTime());
        // Update the drawable texture
        updateDrawableTexture(entity, anim, drawable);
    }
}

void AnimationSystem::registerAnimation_aux(const entt::entity entity, const std::string& basePath,
                                            const entt::id_type stateId,
                                            const Texture::Config& textureConfig, const Clip& clipConfig)
{
    auto& registry = World::getInstance().registry;
    if (!FileUtils::directoryExists(basePath))
    {
        std::cerr << "AnimatorSystem: Animation directory does not exist:" << basePath;
        std::cerr << "Current working directory:" << FileUtils::getAbsolutePath(".");
        throw FileNotFoundException("Animation directory does not exist");
    }
    assert(registry.all_of<Animator>(entity));
    // Get frame count from TextureManager
    Clip clip = clipConfig;
    clip.frames = TextureManager::getInstance().getAllTextures(basePath, textureConfig);
    clip.frameCount = clip.frames.size();
    assert(clip.frameCount > 0);
    registry.patch<Animator>(entity, [stateId, &clip](Animator& animator)
    {
        animator.animations[stateId] = clip;
    });
}

void AnimationSystem::onChange(const AnimationChangeEvent& animationChangeEvent)
{
    auto& registry = World::getInstance().registry;
    const entt::entity entity = animationChangeEvent.entity;
    const entt::id_type stateId = animationChangeEvent.stateId;
    assert(registry.valid( entity)&& "entity is invalid");
    assert(registry.all_of<Animator>(entity)&& "entity does not have Animator component");
    registry.patch<Animator>(entity, [stateId](Animator& animator)
    {
        animator.current = &animator.animations.at(stateId);
        animator.currentFrame = 0;
        animator.elapsedTime = 0;
    });
}


inline void AnimationSystem::updateAnimation(entt::entity entity, Animator& anim, float deltaTime)
{
    if (!anim.current)
    {
        return;
    }

    // Add elapsed time
    anim.elapsedTime += deltaTime;

    // Check if we need to advance to next frame
    if (anim.elapsedTime >= anim.current->frameDuration)
    {
        // How many frames to advance
        const int framesToAdvance = static_cast<int>(anim.elapsedTime / anim.current->frameDuration);
        anim.elapsedTime = std::fmod(anim.elapsedTime, anim.current->frameDuration);
        // Handle frame advancement
        if (anim.current->loop)
        {
            // For looping animations, wrap around
            anim.currentFrame = (anim.currentFrame + framesToAdvance) % anim.current->frameCount;
        }
        else
        {
            // For non-looping animations, clamp at the end
            anim.currentFrame = std::min(anim.currentFrame + framesToAdvance,
                                         anim.current->frameCount - 1);

            // Stop animation when it reaches the end
            if (anim.currentFrame >= anim.current->frameCount - 1)
            {
                anim.isPlaying = false;
            }
        }
        assert(anim.currentFrame >= 0 && anim.currentFrame < anim.current->frameCount);
    }
}

inline void AnimationSystem::updateDrawableTexture(entt::entity entity, const Animator& anim, Drawable& drawable)
{
    // Get the current frame index
    const Texture* texture = anim.current->frames.at(anim.currentFrame);
    assert(texture);
    drawable.texture = texture;
}
