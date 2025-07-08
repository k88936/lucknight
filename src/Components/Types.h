//
// Created by root on 7/3/25.
//

#ifndef TYPES_H
#define TYPES_H

struct TypePlayer
{
    inline static uint64_t category()
    {
        return 1 << 0;
    }
};

struct TypeProjectile
{
    inline static uint64_t category()
    {
        return 1 << 1;
    }
};

struct TypePlatform
{
    inline static uint64_t category()
    {
        return 1 << 2;
    }
};

struct TypeTreasure
{
    inline static uint64_t category()
    {
        return 1 << 3;
    }
};

struct TypeWeapon
{

};



#endif //TYPES_H
