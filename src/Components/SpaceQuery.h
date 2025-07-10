//
// Created by root on 7/7/25.
//

#ifndef SPACEQUERY_H
#define SPACEQUERY_H
#include "Types.h"
#include "../Type/Vector.h"

template <typename Type>
struct SpaceQuery
{
    Vector offset={};
    float radius=0.05;
    bool got;

    inline static uint64_t category()
    {
        return Type::category() << 32;
    };

    inline static uint64_t mask()
    {
        return Type::category();
    }
};
typedef SpaceQuery<TypePlatform> GroundDetector;
typedef SpaceQuery<TypeTreasure> TreasureDetector;
#endif //SPACEQUERY_H
