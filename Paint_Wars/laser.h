#ifndef LASER_H
#define LASER_H

#include "game.h" 
#include "visiblegameobject.h"

class Laser :
  public VisibleGameObject
{
public:
  Laser();
  ~Laser();

  void Update(float elapsedTime);
  void setSpeed(float);
  void setElapsedTime(int);

private:
 float _speed;
 float _elapsedTimeSinceStart;
};

#endif

