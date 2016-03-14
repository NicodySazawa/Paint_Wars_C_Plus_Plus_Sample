#ifndef WEAPONPOWERUP_H
#define WEAPONPOWERUP_H

#include "game.h" 
#include "visiblegameobject.h"

class WeaponPowerUp :
  public VisibleGameObject
{
public:
  WeaponPowerUp();
  ~WeaponPowerUp();

  void Update(float elapsedTime);
  int getPowerUpLevel();
  void setPowerUpLevel(int);
  void setElapsedTime(float);

private:
 float _elapsedTimeSinceStart;
 int powerUpLevel;

 
};

#endif