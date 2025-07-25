//
// Created by kvtoD on 6/30/2025.
//

#ifndef DRAWABLE_H
#define DRAWABLE_H
#include "Texture.h"
#include "../Type/Vector.h"


struct Drawable {
    const Texture* texture = nullptr;
    // bool colored = false;
    Vector color= {1,1,1};
    float alpha = 1.0f;
};
#endif //DRAWABLE_H
