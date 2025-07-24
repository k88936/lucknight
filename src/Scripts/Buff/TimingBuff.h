//
// Created by kvtoD on 7/24/2025.
//

#ifndef TIMINGBUFF_H
#define TIMINGBUFF_H
#include "BuffBase.h"

// TimingBuff that automatically expires after a duration
class TimingBuff : public virtual  BuffBase
{
protected:
    float duration;
    float elapsedTime;
public:
    explicit TimingBuff(const float duration) : duration(duration), elapsedTime(0.0f)
    {
    }

    void onUpdate() override
    {
        elapsedTime += 1.0f; // Assuming called every frame, adjust as needed
    }

    bool isExpired() const override
    {
        return elapsedTime >= duration;
    }
};

#endif //TIMINGBUFF_H
