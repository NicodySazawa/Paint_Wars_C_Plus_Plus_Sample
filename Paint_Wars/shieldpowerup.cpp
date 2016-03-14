#include "shieldpowerup.h"
#include "playership.h"
#include "laser.h"
#include "game.h"
#include <math.h>
#include "servicelocator.h"
ShieldPowerUp::ShieldPowerUp() : _elapsedTimeSinceStart(10.f)
{
  char path[] = "assets/shield.png";
  Load(path);
  assert(IsLoaded());

  sf::Sprite& sprite = GetSprite();
  sf::Vector2f size = sprite.GetSize();
  sprite.SetCenter(size.x / 2, size.y / 2);
}
ShieldPowerUp::~ShieldPowerUp()
{
}
void ShieldPowerUp::Update(float elapsedTime)
{
	  if (elapsedTime < 1.f)
	{
		_elapsedTimeSinceStart -= elapsedTime;
	}
	sf::Rect<float> powerupBoundingBox = GetBoundingRect();

	if( _elapsedTimeSinceStart < 0)
	{
		SetPosition((rand() % Game::SCREEN_WIDTH)/2,((rand() % Game::SCREEN_HEIGHT)/2));
		_elapsedTimeSinceStart = 10;
	}

	PlayerShip* player = dynamic_cast<PlayerShip*>(Game::GetGameObjectManager().Get("Ship1"));
	assert(NULL != player);
	sf::Rect<float> playerBoundingBox = player->GetBoundingRect();

	if(playerBoundingBox.Intersects(powerupBoundingBox))
	{
		ServiceLocator::GetAudio()->PlaySound("assets/Gungan-Shield1.wav");
		player->setElapsedTime(0);
		SetPosition(Game::SCREEN_WIDTH / 2, Game::GetGameField().Top - 100);
		Game::SetScore(Game::GetScore() + 500);
	}
}
void ShieldPowerUp::setElapsedTime(float newTime)
{
	_elapsedTimeSinceStart = newTime;
}