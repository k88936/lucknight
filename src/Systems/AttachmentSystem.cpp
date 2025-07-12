//
// Created by root on 7/10/25.
//

#include "AttachmentSystem.h"
#include "../Components/Attachment.h"


void AttachmentSystem::update()
{
    applyTransform<Weapon>();
    applyTransform<Indicator>();
}
