//
// Created by root on 7/11/25.
//

#ifndef TREASURESYSTEM_H
#define TREASURESYSTEM_H
#include "System.h"
#include "../Events/GainEvents.h"


class TreasureSystem : public System<TreasureSystem>
{
public:
    TreasureSystem();
    ~TreasureSystem() override;
    void update() override;
    void onGainTreasureEvent(const GainTreasure& event);
};


#endif //TREASURESYSTEM_H
