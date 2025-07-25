//
// Created by root on 7/10/25.
//

#ifndef PREFABTREASURE_H
#define PREFABTREASURE_H
#include "Prefab.h"
#include "../Components/Status.h"

class PrefabTreasure :Prefab {
public:

   entt::entity build(const Matrix& transform) override;

   StatusTreasure::Type type;
};


class PrefabTreasureWeapon: public PrefabTreasure
{
   public:
   PrefabTreasureWeapon()
   {
      type = StatusTreasure::Weapon;
   }
   entt::entity build(const Matrix& transform) override;
};
class PrefabTreasureCarrot : public PrefabTreasure
{
   public:
   PrefabTreasureCarrot()
   {
      type = StatusTreasure::Carrot;

   }
   entt::entity build(const Matrix& transform) override;
}  ;

class PrefabTreasureRed : public PrefabTreasure
{
   public:
   PrefabTreasureRed()
   {
      type = StatusTreasure::Red;
   }
   entt::entity build(const Matrix& transform) override;
};
class PrefabTreasureBlue : public PrefabTreasure
{
   public:
   PrefabTreasureBlue()
   {
      type = StatusTreasure::Blue;

   }
   entt::entity build(const Matrix& transform) override;
};
#endif //PREFABTREASURE_H
