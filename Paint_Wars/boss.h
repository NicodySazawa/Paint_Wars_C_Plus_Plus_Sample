#ifndef BOSS_H
#define BOSS_H

#include "game.h" 
#include "ship.h"

class Boss :
  public Ship
{
public:
   Boss();
  ~Boss();

  void Update(float elapsedTime);
  void setElapsedTime(float);
 

private:
   float _elapsedTimeSinceStart;
   float _maxVelocity;
   float _maxThrust;


};

#endif