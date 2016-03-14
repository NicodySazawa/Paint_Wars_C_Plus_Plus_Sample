#ifndef AILASER2_H
#define AILASER2_H

#include "game.h" 
#include "visiblegameobject.h"

class AILaser2 :
  public VisibleGameObject
{
public:
  AILaser2();
  ~AILaser2();

  void Update(float elapsedTime);
   void setElapsedTime(float);
   void setSpeed(float);

private:
 float _speed;
 float _elapsedTimeSinceStart;
};

#endif