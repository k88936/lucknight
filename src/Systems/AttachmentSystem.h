//
// Created by root on 7/10/25.
//

#ifndef ATTACHMENTSYSTEM_H
#define ATTACHMENTSYSTEM_H
#include "System.h"
#include "../Components/relativeTransform.h"
#include "../Components/Transform.h"
#include "../Core/World.h"


class AttachmentSystem : public  System<AttachmentSystem>
{
public:
    void update() override;
};



#endif //ATTACHMENTSYSTEM_H
