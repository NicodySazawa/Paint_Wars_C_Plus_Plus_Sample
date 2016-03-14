#ifndef BOSS_LASER_H
#define BOSS_LASER_H

#include "game.h" 
#include "visiblegameobject.h"

class BossLaser :
  public VisibleGameObject
{
public:
  BossLaser();
  ~BossLaser();

  void Update(float elapsedTime);
  void setSpeed(float,float);
  void setElapsedTime(float);

private:
 float _speedX;
 float _speedY;
 float _elapsedTimeSinceStart;
};

#endif