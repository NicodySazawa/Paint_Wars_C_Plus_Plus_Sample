#include "boss.h"
#include "bosslaser.h"
#include "game.h"
#include "laser.h"
#include "math.h"
#include "playership.h"
#include "servicelocator.h"

Boss::Boss():_elapsedTimeSinceStart(0),_maxThrust(0),_maxVelocity(0)
{
  char path[] = "assets/bosship.png";
  Load(path);
  assert(IsLoaded());

  sf::Sprite& sprite = GetSprite();
  sf::Vector2f size = sprite.GetSize();
  sprite.SetCenter(size.x / 2, size.y / 2);
}
Boss::~Boss()
{
}
void Boss::Update(float elapsedTime)
{	
  if (elapsedTime < 1.f)
  {
    _elapsedTimeSinceStart += elapsedTime;
  }
  
 PlayerShip* ship = static_cast<PlayerShip*>(Game::GetGameObjectManager().Get("Ship1"));
 assert(NULL != ship);
 sf::Vector2f shipPosition = ship->GetPosition();

 BossLaser* bosslaser = dynamic_cast<BossLaser*>(Game::GetGameObjectManager().Get("BossLaser"));
 assert(NULL != bosslaser);

if(_elapsedTimeSinceStart < 10)
{	
	SetPosition	(Game::SCREEN_WIDTH/2, Game::GetGameField().Top - 100);
	_maxVelocity = 0;	
	_maxThrust = 0;
	bosslaser->setSpeed(0,0);
	bosslaser->SetPosition(GetPosition().x,GetPosition().y);
}
if(_elapsedTimeSinceStart > 10 && _elapsedTimeSinceStart < 15)
{
	_maxVelocity = 333;
	_maxThrust = 333;
  if(GetPosition().x < shipPosition.x)
    _velocity += 15.0f;
  else if(GetPosition().x > shipPosition.x)
    _velocity -= 15.0f;
  else
    _velocity = 0.0f;

    if(GetPosition().y< shipPosition.y)
    _thrust += 15.0f;
  else if(GetPosition().x > shipPosition.x)
    _thrust -= 15.0f;
  else
    _thrust = 0.0f;
}
  else if(_elapsedTimeSinceStart >= 15 && _elapsedTimeSinceStart <= 16)
{
	SetPosition	(Game::SCREEN_WIDTH/2, Game::GetGameField().Top - 100);
	_maxVelocity = 0;	
	_maxThrust = 0;
	bosslaser->setSpeed(0,0);
	bosslaser->SetPosition(GetPosition().x,GetPosition().y);
}
else if(_elapsedTimeSinceStart > 25 && _elapsedTimeSinceStart < 30)
{
	_maxVelocity = 666;
	_maxThrust = 666;
  if(GetPosition().x < shipPosition.x)
    _velocity += 15.0f;
  else if(GetPosition().x > shipPosition.x)
    _velocity -= 15.0f;
  else
    _velocity = 0.0f;

    if(GetPosition().y < shipPosition.y)
    _thrust += 15.0f;
  else if(GetPosition().x > shipPosition.x)
    _thrust -= 15.0f;
  else
    _thrust = 0.0f;
}
else if(_elapsedTimeSinceStart >= 30 && _elapsedTimeSinceStart <= 31)
{
	SetPosition	(Game::SCREEN_WIDTH/2, Game::GetGameField().Top - 100);
	_maxVelocity = 0;	
	_maxThrust = 0;
	bosslaser->setSpeed(0,0);
	bosslaser->SetPosition(GetPosition().x,GetPosition().y);
}

else if(_elapsedTimeSinceStart > 40 && _elapsedTimeSinceStart < 45)
{
	_maxVelocity = 999;
	_maxThrust = 999;
  if(GetPosition().x -20 < shipPosition.x)
    _velocity += 15.0f;
  else if(GetPosition().x +20 > shipPosition.x)
    _velocity -= 15.0f;
  else
    _velocity = 0.0f;

    if(GetPosition().y -20 < shipPosition.y)
    _thrust += 15.0f;
  else if(GetPosition().x +20 > shipPosition.x)
    _thrust -= 15.0f;
  else
    _thrust = 0.0f;
}
else if(_elapsedTimeSinceStart >= 45)
{
	_elapsedTimeSinceStart = 30;
	SetPosition(Game::SCREEN_WIDTH/2, Game::GetGameField().Top - 100);
	
}
  if (_velocity > _maxVelocity)
  {
    _velocity = _maxVelocity;
  }
  if (_velocity < -_maxVelocity)
  {
    _velocity = -_maxVelocity;
  }
  if (_thrust > _maxThrust)
  {
    _thrust = _maxThrust;
  }
  if (_thrust < -_maxThrust)
  {
    _thrust = -_maxThrust;
  }

  sf::Rect<float> enemyBoundingBox = GetBoundingRect();
  
	Laser* laser = dynamic_cast<Laser*>(Game::GetGameObjectManager().Get("Laser1"));
	assert(NULL != laser);

	sf::Rect<float> laserBoundingBox = laser->GetBoundingRect();

	if(laserBoundingBox.Intersects(enemyBoundingBox))
	{
		ServiceLocator::GetAudio()->PlaySound("assets/explosion-02.wav");
		SetPosition(rand() % Game::SCREEN_WIDTH, -(rand() % Game::SCREEN_HEIGHT));
		bosslaser->setSpeed(0,0);
		bosslaser->SetPosition(GetPosition().x,GetPosition().y);
		laser->SetPosition(Game::SCREEN_WIDTH/ 2, Game::SCREEN_HEIGHT + 50);
		laser->setSpeed(0.f);
		laser->setElapsedTime(-1);
		if(_elapsedTimeSinceStart >= 10 && _elapsedTimeSinceStart < 20)
		{
			Game::SetScore(Game::GetScore() + 400);
		}
		else if(_elapsedTimeSinceStart >= 25 && _elapsedTimeSinceStart < 40)
		{
			Game::SetScore(Game::GetScore() + 800);
		}
	     else if(_elapsedTimeSinceStart >= 40)
		{
			Game::SetScore(Game::GetScore() + 1200);
		}
	
  }

  sf::Vector2f pos = GetPosition();
  sf::Vector2f spriteSize = GetSprite().GetSize();

   if(pos.x <= spriteSize.x / 2)
  {
    if(_velocity < 0)
    {
      _velocity = -_velocity;
    }
  }
  if(pos.x >= (Game::SCREEN_WIDTH - spriteSize.x / 2))
  {
    if(_velocity > 0)
    {
      _velocity = -_velocity;
    }
  }
  if(pos.y <= spriteSize.y / 2)
  {
    if(_thrust < 0)
    {
      _thrust = -_thrust;
    }
  }
  if(pos.y >= (Game::SCREEN_HEIGHT - spriteSize.y / 2))
  {
    if(_thrust > 0)
    {
      _thrust = -_thrust;
    }
  }

  GetSprite().Move(_velocity * elapsedTime, _thrust * elapsedTime);
  setShipPosX(pos.x);
  setShipPosY(pos.y);

}
void Boss::setElapsedTime(float newTime)
{
	_elapsedTimeSinceStart = newTime;
}