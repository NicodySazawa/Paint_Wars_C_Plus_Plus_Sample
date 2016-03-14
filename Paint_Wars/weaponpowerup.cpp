#include "weaponpowerup.h"
#include "playership.h"
#include "laser.h"
#include "game.h"
#include "servicelocator.h"
#include <math.h>
WeaponPowerUp::WeaponPowerUp() : _elapsedTimeSinceStart(20.f),powerUpLevel(1)
{
  char path[] = "assets/sword.png";
  Load(path);
  assert(IsLoaded());

  sf::Sprite& sprite = GetSprite();
  sf::Vector2f size = sprite.GetSize();
  sprite.SetCenter(size.x / 2, size.y / 2);
}
WeaponPowerUp::~WeaponPowerUp()
{
}
void WeaponPowerUp::Update(float elapsedTime)
{
  if (elapsedTime < 1.f)
	{
		_elapsedTimeSinceStart -= elapsedTime;
	}
	sf::Rect<float> powerupBoundingBox = GetBoundingRect();

	if( _elapsedTimeSinceStart < 0)
	{
		SetPosition((rand() % Game::SCREEN_WIDTH)/2,((rand() % Game::SCREEN_HEIGHT)/2));
		_elapsedTimeSinceStart = 20;
	}

	PlayerShip* player = dynamic_cast<PlayerShip*>(Game::GetGameObjectManager().Get("Ship1"));
	assert(NULL != player);
	Laser* laser = dynamic_cast<Laser*>(Game::GetGameObjectManager().Get("Laser1"));
	
	sf::Rect<float> playerBoundingBox = player->GetBoundingRect();

	if(playerBoundingBox.Intersects(powerupBoundingBox))
	{
		ServiceLocator::GetAudio()->PlaySound("assets/Gungan-Shield2.wav");
		SetPosition(Game::SCREEN_WIDTH / 2, Game::GetGameField().Top - 100);
		Game::SetScore(Game::GetScore() + 1000);
		powerUpLevel++;
	}
}
int WeaponPowerUp::getPowerUpLevel()
{
	return powerUpLevel;
}
void WeaponPowerUp::setPowerUpLevel(int newPower)
{
	powerUpLevel = newPower;
}
void WeaponPowerUp::setElapsedTime(float newTime)
{
	_elapsedTimeSinceStart = newTime;
}