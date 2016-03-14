#include "aiship.h"
#include "game.h"
#include "laser.h"
#include "math.h"
#include "playership.h"
#include "servicelocator.h"

AIShip::AIShip():_elapsedTimeSinceStart(0)
{
  char path[] = "assets/aiship.png";
  Load(path);
  assert(IsLoaded());

  sf::Sprite& sprite = GetSprite();
  sf::Vector2f size = sprite.GetSize();
  sprite.SetCenter(size.x / 2, size.y / 2);
}
AIShip::~AIShip()
{
}
void AIShip::Update(float elapsedTime)
{	
  if (elapsedTime < 1.f)
  {
    _elapsedTimeSinceStart += elapsedTime;
  }
  if(_elapsedTimeSinceStart < 6)
  {
     _thrust = rand() % 300;
     _velocity = -(rand() % 300);
  }
  else if(_elapsedTimeSinceStart < 12)
  {
     _thrust = rand() % 300;
     _velocity = rand() % 300;
  }
  else if(_elapsedTimeSinceStart < 17)
  {
     _thrust = rand() % 500;
     _velocity = -(rand() % 500);
  }
  else if(_elapsedTimeSinceStart < 22)
  {
     _thrust = rand() % 500;
     _velocity = rand() % 500;
  }
    else if(_elapsedTimeSinceStart < 26)
  {
     _thrust = rand() % 600;
     _velocity = -(rand() % 600);
  }
  else if(_elapsedTimeSinceStart < 30)
  {
     _thrust = rand() % 600;
     _velocity = rand() % 600;
  }
    else if(_elapsedTimeSinceStart < 33)
  {
     _thrust = rand() % 700;
     _velocity = -(rand() % 700);
  }
  else if(_elapsedTimeSinceStart < 36)
  {
     _thrust = rand() % 700;
     _velocity = rand() % 700;
  }
    else if(_elapsedTimeSinceStart < 38)
  {
     _thrust = rand() % 800;
     _velocity = -(rand() % 800);
  }
    else if(_elapsedTimeSinceStart < 40)
  {
     _thrust = rand() % 800;
     _velocity = rand() % 800;
  }
    else if(_elapsedTimeSinceStart < 41)
  {
     _thrust = rand() % 900;
     _velocity = -(rand() % 900);
  }
   else if(_elapsedTimeSinceStart < 42)
  {
     _thrust = rand() % 900;
     _velocity = rand() % 900;
  }
   else if(_elapsedTimeSinceStart > 43)
  {
     _thrust = rand() % 900;
     _velocity = -(rand() % 900);
	 _elapsedTimeSinceStart = 40;
  }
  sf::Vector2f pos = GetPosition();
  sf::Vector2f spriteSize = GetSprite().GetSize();

  if(pos.x <= spriteSize.x / 2)
  {
	SetPosition(rand() % Game::SCREEN_WIDTH, -(rand() % Game::SCREEN_HEIGHT / 2));
  }
  if(pos.x >= (Game::SCREEN_WIDTH - spriteSize.x / 2))
  {
	SetPosition(rand() % Game::SCREEN_WIDTH, -(rand() % Game::SCREEN_HEIGHT / 2));
  }
  if(pos.y >= (Game::SCREEN_HEIGHT - spriteSize.y / 2))
  {
	SetPosition(rand() % Game::SCREEN_WIDTH, -(rand() % Game::SCREEN_HEIGHT / 2));
  }
  
  std::vector<std::string> lasers;
  lasers.push_back("Laser1");

  sf::Rect<float> enemyBoundingBox = GetBoundingRect();
  
  for(unsigned int i = 0; i < lasers.size(); i++)
  {
	Laser* laser = dynamic_cast<Laser*>(Game::GetGameObjectManager().Get(lasers[i]));
	assert(NULL != laser);

	sf::Rect<float> laserBoundingBox = laser->GetBoundingRect();

	if(laserBoundingBox.Intersects(enemyBoundingBox))
	{
		ServiceLocator::GetAudio()->PlaySound("assets/explosion-01.wav");
		SetPosition(rand() % Game::SCREEN_WIDTH, -(rand() % 200));
		laser->SetPosition(Game::SCREEN_WIDTH/ 2, Game::SCREEN_HEIGHT + 50);
		laser->setSpeed(0.f);
		laser->setElapsedTime(-1);
		if(_elapsedTimeSinceStart < 20)
		{
			Game::SetScore(Game::GetScore() + 200);
		}
		else if(_elapsedTimeSinceStart < 40)
		{
			Game::SetScore(Game::GetScore() + 400);
		}
	     else if(_elapsedTimeSinceStart >= 40)
		{
			Game::SetScore(Game::GetScore() + 600);
		}
	}
  }

  GetSprite().Move(_velocity * elapsedTime, _thrust * elapsedTime);
  setShipPosX(pos.x);
  setShipPosY(pos.y);
}
void AIShip::setElapsedTime(float newTime)
{
	_elapsedTimeSinceStart = newTime;
}
