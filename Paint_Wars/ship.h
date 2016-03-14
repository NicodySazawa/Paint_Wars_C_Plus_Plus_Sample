#ifndef SHIP_H
#define SHIP_H

#include "game.h" 
#include "visiblegameobject.h"

class Ship :
  public VisibleGameObject
{
public:
  Ship();
  ~Ship();

  float GetVelocity();
  int getShipPosX();
  int getShipPosY();
  void setShipPosX(int);
  void setShipPosY(int);
  int getAmmo();

protected:
  float _velocity;
  float _maxVelocity;
  float _thrust;
  float _maxThrust;
  int shipPosX;
  int shipPosY;
};

#endif
