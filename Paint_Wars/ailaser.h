#ifndef AILASER_H
#define AILASER_H

#include "game.h" 
#include "visiblegameobject.h"

class AILaser :
  public VisibleGameObject
{
public:
  AILaser();
  ~AILaser();

  void Update(float elapsedTime);
  void setElapsedTime(float);
  void setSpeed(float);

private:
 float _speed;
 float _elapsedTimeSinceStart;

 
};

#endif