//
// Created by kvtoD on 7/24/2025.
//

#ifndef TIMINGEXPIREDMIXIN_H
#define TIMINGEXPIREDMIXIN_H
#include "BuffBase.h"
#include "ExpiredMixin.h"

// TimingBuff that automatically expires after a duration
struct TimingExpiredMixin: public ExpiredMixin
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
    void reset() override
    {
        elapsedTime = 0.0f;
    }

    bool isExpired() const override
    {
        return elapsedTime >= duration;
    }
};

#endif //TIMINGEXPIREDMIXIN_H
