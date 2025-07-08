//
// Created by kvtoD on 6/30/2025.
//

#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "../Type/Matrix.h"

struct Transform {
    Matrix matrix;
    // In your Transform class or header
};

inline std::ostream& operator<<(std::ostream& os,const Transform& transform )  {
    return os<< "Transform{matrix: " <<transform.matrix<<"}";
}
#endif //TRANSFORM_H
