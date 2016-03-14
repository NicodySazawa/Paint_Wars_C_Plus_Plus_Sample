#ifndef AILASER3_H
#define AILASER3_H

#include "game.h" 
#include "visiblegameobject.h"

class AILaser3 :
  public VisibleGameObject
{
public:
  AILaser3();
  ~AILaser3();

  void Update(float elapsedTime);
   void setElapsedTime(float);
   void setSpeed(float);

private:
 float _speed;
 float _elapsedTimeSinceStart;
};

#endif