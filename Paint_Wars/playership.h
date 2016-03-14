#ifndef PLAYER_SHIP_H
#define PLAYER_SHIP_H

#include "game.h" 
#include "ship.h"

class PlayerShip :
  public Ship
{
public:
   PlayerShip();
  ~PlayerShip();

  void Update(float elapsedTime);
  void setElapsedTime(float);
  
private: 
  float _elapsedTimeSinceStart;

};

#endif
