//
// Created by kvtoD on 6/30/2025.
//

#ifndef PREFABPLAYER_H
#define PREFABPLAYER_H
#include "Prefab.h"
#include "../Components/Keymap.h"


class  PrefabPlayer: public Prefab{

public:
    ~PrefabPlayer() override = default;
    entt::entity build(const Matrix &transform = Matrix()) override;
    Keymap keymap;
private:
    // Initialize animations for the player entity
};




#endif //PREFABPLAYER_H
