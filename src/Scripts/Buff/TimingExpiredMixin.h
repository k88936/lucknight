//
// Created by kvtoD on 7/24/2025.
//

#ifndef TIMINGEXPIREDMIXIN_H
#define TIMINGEXPIREDMIXIN_H
#include "BuffBase.h"

// TimingBuff that automatically expires after a duration
struct TimingExpiredMixin
{
protected:
    float duration;
    float elapsedTime;

    explicit TimingExpiredMixin(const float duration) : duration(duration), elapsedTime(0.0f)
    {
    }

    void updateTiming()
    {
        elapsedTime += World::getInstance().getFrameDeltaTime(); // Assuming called every frame, adjust as needed
    }

public:
    void reset()
    {
        elapsedTime = 0.0f;
    }

    bool isExpired() const
    {
        return elapsedTime >= duration;
    }
};

#endif //TIMINGEXPIREDMIXIN_H
