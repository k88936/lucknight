//
// Created by root on 7/11/25.
//

#ifndef TREASURESYSTEM_H
#define TREASURESYSTEM_H
#include "System.h"
#include "../Events/GainEvents.h"
#include <random>
#include <chrono>


class TreasureSystem : public System<TreasureSystem>
{
public:
    TreasureSystem();
    ~TreasureSystem() override;
    void update() override;
    void onGainTreasureEvent(const GainTreasure& event);

private:
    float spawnTimer = 0.0f;
    float spawnInterval = 3.0f; // seconds, will be randomized
    std::mt19937 rng;
    std::uniform_real_distribution<float> posDistX;
    std::uniform_real_distribution<float> posDistY;
    std::uniform_real_distribution<float> intervalDist;
    std::uniform_int_distribution<int> treasureTypeDist;
    std::chrono::steady_clock::time_point lastUpdate;
    void spawnRandomTreasure();
};


#endif //TREASURESYSTEM_H
