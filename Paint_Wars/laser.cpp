#include "laser.h"
#include "playership.h"
#include "aiship.h"
#include "game.h"
#include <string>
#include "servicelocator.h"
#include <math.h>
#include "weaponpowerup.h"

Laser::Laser() :
  _speed(0.f)
  ,_elapsedTimeSinceStart(0.f)
{
  char path[] = "assets/playerlaser1.png";
  Load(path);
  assert(IsLoaded());

  sf::Sprite& sprite = GetSprite();
  sf::Vector2f size = sprite.GetSize();
  sprite.SetCenter(size.x / 2, size.y / 2);
}
Laser::~Laser()
{
}
void Laser::Update(float elapsedTime)
{
  if (elapsedTime < 1.f)
  {
    _elapsedTimeSinceStart -= elapsedTime;
  }
  
  sf::Vector2f spriteSize = GetSprite().GetSize();
  sf::Vector2f pos = GetPosition();
	
  
  sf::Rect<float> laserBoundingBox = GetBoundingRect();

	PlayerShip* player = dynamic_cast<PlayerShip*>(Game::GetGameObjectManager().Get("Ship1"));
	assert(NULL != player);

	WeaponPowerUp* weapon = dynamic_cast<WeaponPowerUp*>(Game::GetGameObjectManager().Get("WeaponPowerUp"));


	if(Game::GetInput().IsKeyDown(sf::Key::Space) && _elapsedTimeSinceStart < 0)
  {
	  int power = weapon->getPowerUpLevel();
	  SetPosition(player->getShipPosX(),player->getShipPosY() - 30);
	  ServiceLocator::GetAudio()->PlaySound("assets/XWing-Laser.wav");
	  _speed = (-1500.f * power);
	  _elapsedTimeSinceStart = 2.f;
  }
  if(pos.y <= spriteSize.y / 2)
	{
		SetPosition(Game::SCREEN_WIDTH / 2, Game::SCREEN_HEIGHT + 100);
	  _speed = 0.f;
	  _elapsedTimeSinceStart = -1;
	}
 GetSprite().Move(0, _speed * elapsedTime);
  
}
void Laser::setSpeed(float newSpeed)
{
	_speed = newSpeed;
}
void Laser::setElapsedTime(int newTime)
{
	_elapsedTimeSinceStart = newTime;
}