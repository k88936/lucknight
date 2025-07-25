//
// Created by root on 7/10/25.
//

#include "AttachmentSystem.h"
#include "../Components/Attachment.h"


AttachmentSystem::AttachmentSystem()
{
    connectDestroyListener<Weapon>();
    connectDestroyListener<Indicator>();
    connectDestroyListener<TextureOnly>();
}

AttachmentSystem::~AttachmentSystem()
{
    disconnectDestroyListener<Weapon>();
    disconnectDestroyListener<Indicator>();
    disconnectDestroyListener<TextureOnly>();
}

void AttachmentSystem::update()
{
    applyTransform<Weapon>();
    applyTransform<Indicator>();
    applyTransform<TextureOnly>();
}
