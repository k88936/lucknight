//
// Created by root on 7/12/25.
//

#ifndef INDICATORSCRIPT_H
#define INDICATORSCRIPT_H
#include "Script.h"
#include "../Components/Drawable.h"
#include "../Components/Transform.h"

SCRIPT(IndicatorScript, (Transform)(Drawable))
{
public:
    float value = 0;
    std::vector<const Texture*> frames;

    void init() override
    {
        assert(frames.size()>0);
        componentDrawable->texture = frames.at(0);
    }

    void update() override
    {
        const size_t n = std::min(frames.size() - 1, static_cast<size_t>(value * frames.size()));
        componentDrawable->texture = frames.at(n);
    }
};


#endif //INDICATORSCRIPT_H
