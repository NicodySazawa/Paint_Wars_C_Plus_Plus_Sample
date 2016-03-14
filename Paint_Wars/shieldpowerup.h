#ifndef SHIELDPOWERUP_H
#define SHIELDPOWERUP_H

#include "game.h" 
#include "visiblegameobject.h"

class ShieldPowerUp :
  public VisibleGameObject
{
public:
  ShieldPowerUp();
  ~ShieldPowerUp();

  void Update(float elapsedTime);
  void setElapsedTime(float);

private:
 float _elapsedTimeSinceStart;
 
};

#endif