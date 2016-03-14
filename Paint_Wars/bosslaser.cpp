#include "bosslaser.h"
#include "playership.h"
#include "boss.h"
#include "game.h"
#include <string>
#include "servicelocator.h"
#include <math.h>

BossLaser::BossLaser() : 
	_speedX(0.f),_speedY(0.f)
  ,_elapsedTimeSinceStart(0.f)
{
  char path[] = "assets/bosslaser.png";
  Load(path);
  assert(IsLoaded());

  sf::Sprite& sprite = GetSprite();
  sf::Vector2f size = sprite.GetSize();
  sprite.SetCenter(size.x / 2, size.y / 2);
}
BossLaser::~BossLaser()
{
}
void BossLaser::Update(float elapsedTime)
{
  if (elapsedTime < 1.f)
  {
    _elapsedTimeSinceStart += elapsedTime;
  }
  
	Boss* boss = dynamic_cast<Boss*>(Game::GetGameObjectManager().Get("Boss"));
	assert(NULL != boss);

	if((_elapsedTimeSinceStart > .33f) && (boss->getShipPosY() > Game::GetGameField().Top))
	{
		ServiceLocator::GetAudio()->PlaySound("assets/Slave1-Guns.wav");
		SetPosition(boss->getShipPosX(), boss->getShipPosY());
		int random = (rand() % 81);
		if(random < 10)
		{
		  _speedY  = 600.f;
		  _speedX = 600.f;
		}
		else if(random < 20)
		{
			_speedY =  600.f;
			_speedX = -600.f;
		}
		else if(random < 30)
		{
			_speedY = -600.f;
			_speedX = -600.f;
		}
		else if(random < 40)
		{
			_speedY =  -600.f;
			_speedX =   600.f;
		}
		else if(random < 50)
		{
			_speedY =  600.f;
			_speedX =  0.f;
		}
		else if(random < 60)
		{
			_speedY =  -600.f;
			_speedX =  0.f;
		}
		else if(random < 70)
		{
			_speedY =  0.f;
			_speedX =  600.f;
		}
		else if(random < 80)
		{
			_speedY =  0.f;
			_speedX =  -600.f;
		}

		_elapsedTimeSinceStart = 0;
	}
  sf::Vector2f pos = GetPosition();
  sf::Vector2f spriteSize = GetSprite().GetSize();
  if(pos.x <= spriteSize.x / 2)
  {
	  SetPosition(boss->getShipPosX(),boss->getShipPosY());
	  setSpeed(0,0);
  }
  if(pos.x >= (Game::SCREEN_WIDTH - spriteSize.x / 2))
  {
	SetPosition(boss->getShipPosX(),boss->getShipPosY());
	setSpeed(0,0);
  }
  if(pos.y >= (Game::SCREEN_HEIGHT))
  {
	SetPosition(boss->getShipPosX(),boss->getShipPosY());
	setSpeed(0,0);
  }
  
  GetSprite().Move(_speedX * elapsedTime, _speedY * elapsedTime);
}
void BossLaser::setElapsedTime(float newTime)
{
	_elapsedTimeSinceStart = newTime;
}
void BossLaser::setSpeed(float newSpeedX,float newSpeedY)
{
	_speedX = newSpeedX;
	_speedY = newSpeedY;
}