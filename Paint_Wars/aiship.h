#ifndef AI_SHIP_H
#define AI_SHIP_H

#include "game.h" 
#include "ship.h"

class AIShip :
  public Ship
{
public:
   AIShip();
  ~AIShip();

  void Update(float elapsedTime);
  void setElapsedTime(float);

private:

  float _elapsedTimeSinceStart;

};

#endif