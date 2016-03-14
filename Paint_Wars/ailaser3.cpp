#include "ailaser3.h"
#include "playership.h"
#include "aiship.h"
#include "game.h"
#include <string>
#include "servicelocator.h"
#include <math.h>

AILaser3::AILaser3() :
  _speed(0.f)
  ,_elapsedTimeSinceStart(0.f)
{
  char path[] = "assets/enemylaser.png";
  Load(path);
  assert(IsLoaded());

  sf::Sprite& sprite = GetSprite();
  sf::Vector2f size = sprite.GetSize();
  sprite.SetCenter(size.x / 2, size.y / 2);
}
AILaser3::~AILaser3()
{
}
void AILaser3::Update(float elapsedTime)
{
  if (elapsedTime < 1.f)
  {
    _elapsedTimeSinceStart += elapsedTime;
  }
  
	AIShip* enemy = dynamic_cast<AIShip*>(Game::GetGameObjectManager().Get("Enemy3"));
	assert(NULL != enemy);

	if(_elapsedTimeSinceStart > 2)
	{
		ServiceLocator::GetAudio()->PlaySound("assets/TIE-Fire.wav");
		SetPosition(enemy->getShipPosX(), enemy->getShipPosY());
		_speed  = +700.f;
		_elapsedTimeSinceStart = 0;
	}
  sf::Vector2f pos = GetPosition();
  sf::Vector2f spriteSize = GetSprite().GetSize();
  if(pos.x <= spriteSize.x / 2)
  {
	  SetPosition(enemy->getShipPosX(), enemy->getShipPosY());
  }
  if(pos.x >= (Game::SCREEN_WIDTH - spriteSize.x / 2))
  {
	SetPosition(enemy->getShipPosX(), enemy->getShipPosY());
  }
  if(pos.y >= (Game::SCREEN_HEIGHT))
  {
	SetPosition(enemy->getShipPosX(), enemy->getShipPosY());
  }
  
   GetSprite().Move(0, _speed * elapsedTime);

}
void AILaser3::setElapsedTime(float newTime)
{
	_elapsedTimeSinceStart = newTime;
}
void AILaser3::setSpeed(float newSpeed)
{
	_speed = newSpeed;
}