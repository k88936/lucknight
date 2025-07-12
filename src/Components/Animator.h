//
// Created on 7/4/25.
//

#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <unordered_map>
#include <vector>
#include "Texture.h"


// Animation clip data structure
struct Clip
{
    float frameDuration = 0.16f; // Duration of each frame in seconds
    bool loop = true; // Whether the animation should loop
    int frameCount = 0;
    std::vector<const Texture*> frames;
};

// Animation component for entities
struct Animator
{

    // Map from entity state to animation clips
    std::unordered_map<entt::id_type, Clip> animations;
    // Current animation state
    int currentFrame = 0; // Current frame index
    float elapsedTime = 0.0f; // Time accumulated for current frame
    Clip* current;
    bool isPlaying = false;
};

#endif //ANIMATOR_H
