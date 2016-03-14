#include "playership.h"
#include "game.h"
#include "laser.h"
#include "aiship.h"
#include "ailaser.h"
#include "ailaser2.h"
#include "ailaser3.h"
#include "boss.h"
#include "bosslaser.h"

PlayerShip::PlayerShip():_elapsedTimeSinceStart(0)
{
  char path[] = "assets/playership.png";
  Load(path);
  assert(IsLoaded());

  sf::Sprite& sprite = GetSprite();
  sf::Vector2f size = sprite.GetSize();
  sprite.SetCenter(size.x / 2, size.y / 2);
}
PlayerShip::~PlayerShip()
{
}
void PlayerShip::Update(float elapsedTime)
{
	sf::RenderWindow& window = Game::GetWindow();

    if (elapsedTime < 1.f)
  {
    _elapsedTimeSinceStart += elapsedTime;
  }
  
  if(_elapsedTimeSinceStart > 0.f && _elapsedTimeSinceStart < 1.f)
  {
	sf::String timer = sf::String("5 second(s) til vulnerability!");
	timer.SetX(Game::SCREEN_WIDTH / 2 - 125);
	window.Draw(timer);
  }
    if(_elapsedTimeSinceStart > 1.f && _elapsedTimeSinceStart < 2.f)
  {
	sf::String timer = sf::String("4 second(s) til vulnerability!");
	timer.SetX(Game::SCREEN_WIDTH / 2 - 125);
	window.Draw(timer);
  }
	  if(_elapsedTimeSinceStart > 2.f && _elapsedTimeSinceStart < 3.f)
  {
	sf::String timer = sf::String("3 second(s) til vulnerability!");
	timer.SetX(Game::SCREEN_WIDTH / 2 - 125);
	window.Draw(timer);
  }
  if(_elapsedTimeSinceStart > 3.f && _elapsedTimeSinceStart < 4.f)
  {
	sf::String timer = sf::String("2 second(s) til vulnerability!");
	timer.SetX(Game::SCREEN_WIDTH / 2 - 125);
	window.Draw(timer);
  }
  if(_elapsedTimeSinceStart > 4.f && _elapsedTimeSinceStart < 5.f)
  {
	sf::String timer = sf::String("1 second(s) til vulnerability!");
	timer.SetX(Game::SCREEN_WIDTH / 2 - 125);
	window.Draw(timer);
  }
  if(_elapsedTimeSinceStart >= 5.f)
  {
	sf::String timer = sf::String("Don't get hit!                ");
	timer.SetX(Game::SCREEN_WIDTH / 2 - 100);
	window.Draw(timer);
  }
  	
  float acceleration = 20.f;
  if(Game::GetInput().IsKeyDown(sf::Key::Left))
  {
    if(_velocity > 0)
    {
      _velocity = 0.f;
    }
    _velocity -= acceleration;
	_thrust = 0;
  }
  if(Game::GetInput().IsKeyDown(sf::Key::Right))
  {
    if(_velocity < 0)
    {
      _velocity = 0.f;
    }
    _velocity += acceleration;
  }
    if(Game::GetInput().IsKeyDown(sf::Key::Up))
  {
    if(_thrust > 0)
    {
      _thrust = 0.f;
    }
    _thrust -= acceleration;
  }
  if(Game::GetInput().IsKeyDown(sf::Key::Down))
  {
    if(_thrust < 0)
    {
      _thrust = 0.f;
    }
    _thrust += acceleration;
  }
  if(!Game::GetInput().IsKeyDown(sf::Key::Left) &&
     !Game::GetInput().IsKeyDown(sf::Key::Right))
  {
    float deceleration = 1500.f;
    if (_velocity < -deceleration)
    {
      _velocity += deceleration;
    }
    else if (_velocity > deceleration)
    {
      _velocity -= deceleration;
    } else
    {
      _velocity = 0.f;
    }
  }
    if(!Game::GetInput().IsKeyDown(sf::Key::Up) &&
	  !Game::GetInput().IsKeyDown(sf::Key::Down))
  {
    float deceleration = 995.f;
    if (_thrust < -deceleration)
    {
      _thrust += deceleration;
    }
    else if (_thrust > deceleration)
    {
      _thrust -= deceleration;
    } else
    {
      _thrust = 0.f;
    }
  }
	if(Game::GetInput().IsKeyDown(sf::Key::Left) && Game::GetInput().IsKeyDown(sf::Key::Down))
	{
		_thrust -= _velocity;
	}
	if(Game::GetInput().IsKeyDown(sf::Key::Left) && Game::GetInput().IsKeyDown(sf::Key::Up))
	{
		_thrust += _velocity;
	}
  if(_velocity > _maxVelocity)
  {
    _velocity = _maxVelocity;
  }
  if(_velocity < -_maxVelocity)
  {
    _velocity = -_maxVelocity;
  }
  
  if(_thrust > _maxThrust)
  {
    _thrust = _maxThrust;
  }
  if(_thrust < -_maxThrust)
  {
    _thrust = -_maxThrust;
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
  std::vector<std::string> enemies;
  enemies.push_back("Enemy1");
  enemies.push_back("Enemy2");
  enemies.push_back("Enemy3");

  sf::Rect<float> playerBoundingBox = GetBoundingRect();
  for(unsigned int i = 0; i < enemies.size(); i++)
  {
  AIShip* enemy = dynamic_cast<AIShip*>(Game::GetGameObjectManager().Get(enemies[i]));
	assert(NULL != enemy);
	
	sf::Rect<float> enemyBoundingBox = enemy->GetBoundingRect();

	if(enemyBoundingBox.Intersects(playerBoundingBox) && _elapsedTimeSinceStart > 5)
	{
		Game::gotHit();
		SetPosition(Game::SCREEN_WIDTH/2, Game::GetGameField().Bottom - 40);
		_elapsedTimeSinceStart = 0;
	}
  }
 
  AILaser* laser1 = dynamic_cast<AILaser*>(Game::GetGameObjectManager().Get("AILaser1"));
	assert(NULL != laser1);
	
	sf::Rect<float> laser1BoundingBox = laser1->GetBoundingRect();

	if((laser1BoundingBox.Intersects(playerBoundingBox) && _elapsedTimeSinceStart >= 5))
	{
		Game::gotHit();
		SetPosition(Game::SCREEN_WIDTH/2, Game::GetGameField().Bottom - 40);
		_elapsedTimeSinceStart = 0;
	}

  AILaser2* laser2 = dynamic_cast<AILaser2*>(Game::GetGameObjectManager().Get("AILaser2"));
	assert(NULL != laser2);
	
	sf::Rect<float> laser2BoundingBox = laser2->GetBoundingRect();

	if(laser2BoundingBox.Intersects(playerBoundingBox) && _elapsedTimeSinceStart > 5)
	{
		Game::gotHit();
		SetPosition(Game::SCREEN_WIDTH/2, Game::GetGameField().Bottom - 40);
		_elapsedTimeSinceStart = 0;
	}
  
  
  AILaser3* laser3 = dynamic_cast<AILaser3*>(Game::GetGameObjectManager().Get("AILaser3"));
	assert(NULL != laser3);
	
	sf::Rect<float> laser3BoundingBox = laser3->GetBoundingRect();

	if(laser3BoundingBox.Intersects(playerBoundingBox) && _elapsedTimeSinceStart > 5)
	{
		Game::gotHit();
		SetPosition(Game::SCREEN_WIDTH/2, Game::GetGameField().Bottom - 40);
		_elapsedTimeSinceStart = 0;
	}
	  BossLaser* bosslaser = dynamic_cast<BossLaser*>(Game::GetGameObjectManager().Get("BossLaser"));
	assert(NULL != bosslaser);
	
	sf::Rect<float> bosslaserBoundingBox = bosslaser->GetBoundingRect();

	if(bosslaserBoundingBox.Intersects(playerBoundingBox) && _elapsedTimeSinceStart > 5)
	{
		Game::gotHit();
		SetPosition(Game::SCREEN_WIDTH/2, Game::GetGameField().Bottom - 40);
		_elapsedTimeSinceStart = 0;
	}
    Boss* boss = dynamic_cast<Boss*>(Game::GetGameObjectManager().Get("Boss"));
	assert(NULL != boss);
	
	sf::Rect<float> bossBoundingBox = boss->GetBoundingRect();

	if(bossBoundingBox.Intersects(playerBoundingBox) && _elapsedTimeSinceStart > 5)
	{
		Game::gotHit();
		SetPosition(Game::SCREEN_WIDTH/2, Game::GetGameField().Bottom - 40);
		_elapsedTimeSinceStart = 0;
	}
 

  GetSprite().Move(_velocity * elapsedTime, _thrust * elapsedTime);
  setShipPosX(pos.x);
  setShipPosY(pos.y);
 }
 void PlayerShip::setElapsedTime(float newTime)
 {
	 _elapsedTimeSinceStart = newTime;
 }
