#include "game.h"
#include "splashscreen.h"
#include "instructionscreen.h"
#include "mainmenu.h"
#include "playership.h"
#include "aiship.h"
#include "laser.h"
#include "ailaser.h"
#include "ailaser2.h"
#include "ailaser3.h"
#include "servicelocator.h"
#include "sfmlsoundprovider.h"
#include "boss.h"
#include "bosslaser.h"
#include "weaponpowerup.h"
#include "shieldpowerup.h"

void Game::Start(void)
{
  if(_gameState != Uninitialized)
    return;

  _mainWindow.Create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32),"Paint Wars!");

  SFMLSoundProvider soundProvider;
  ServiceLocator::RegisterAudioService(&soundProvider);

  ServiceLocator::GetAudio()->PlaySong("assets/NewSoundtrack.ogg",true);

  PlayerShip *player1 = new PlayerShip();
  player1->SetPosition(SCREEN_WIDTH/2, _gameField.Bottom - 40);
  _gameObjectManager.Add("Ship1", player1);
  Laser *laser1 = new Laser();
  laser1->SetPosition(Game::SCREEN_WIDTH / 2, Game::SCREEN_HEIGHT + 100);
  _gameObjectManager.Add("Laser1", laser1);
   AIShip *enemy1 = new AIShip();
   enemy1->SetPosition(SCREEN_WIDTH/2, _gameField.Top);
   _gameObjectManager.Add("Enemy1", enemy1);
   AIShip *enemy2 = new AIShip();
   enemy2->SetPosition(SCREEN_WIDTH/2, _gameField.Top);
   _gameObjectManager.Add("Enemy2", enemy2);
   AIShip *enemy3 = new AIShip();
   enemy3->SetPosition(SCREEN_WIDTH/2, _gameField.Top);
   _gameObjectManager.Add("Enemy3", enemy3);
   AILaser *ailaser1 = new AILaser();
   ailaser1->SetPosition(SCREEN_WIDTH/2, _gameField.Top - 100);
   _gameObjectManager.Add("AILaser1", ailaser1);
   AILaser2 *ailaser2 = new AILaser2();
   ailaser2->SetPosition(SCREEN_WIDTH/2, _gameField.Top - 100);
   _gameObjectManager.Add("AILaser2", ailaser2);
   AILaser3 *ailaser3 = new AILaser3();
   ailaser3->SetPosition(SCREEN_WIDTH/2, _gameField.Top - 100);
   _gameObjectManager.Add("AILaser3", ailaser3);
   Boss *boss = new Boss();
   boss->SetPosition(SCREEN_WIDTH/2, _gameField.Top - 100);
   _gameObjectManager.Add("Boss", boss);
   BossLaser *bosslaser = new BossLaser();
   bosslaser->SetPosition(SCREEN_WIDTH/2, _gameField.Top - 100);
   _gameObjectManager.Add("BossLaser",bosslaser);
   WeaponPowerUp *weaponpowerup = new WeaponPowerUp();
    weaponpowerup->SetPosition(SCREEN_WIDTH/2, _gameField.Top - 100);
   _gameObjectManager.Add("WeaponPowerUp",weaponpowerup);
    ShieldPowerUp *shieldpowerup = new ShieldPowerUp();
    shieldpowerup->SetPosition(SCREEN_WIDTH/2, _gameField.Top - 100);
   _gameObjectManager.Add("ShieldPowerUp",shieldpowerup);
   
   _gameState = Game::ShowingSplash;

  while(!IsExiting())
  {
    GameLoop();
  }

  _mainWindow.Close();
}
sf::RenderWindow& Game::GetWindow()
{
  return _mainWindow;
}
const sf::Input& Game::GetInput()
{
  return _mainWindow.GetInput();
}
GameObjectManager& Game::GetGameObjectManager()
{
  return _gameObjectManager;
}
const sf::Rect<int> Game::GetGameField()
{
  return _gameField;
}
int Game::GetScore()
{
  return _score;
}
void Game::SetScore(int newScore)
{
	_score = newScore;
}
bool Game::IsExiting()
{
  if(_gameState == Game::Exiting)
    return true;
  else
    return false;
}
void Game::ShowSplashScreen()
{	
  SplashScreen splashScreen;

  splashScreen.Show(_mainWindow);
 _gameState = Game::ShowingMenu;
}
void Game::ShowMenu()
{
  MainMenu mainMenu;
  MainMenu::MenuResult result = mainMenu.Show(_mainWindow);
  switch(result)
  {
  case MainMenu::Exit:
     _gameState = Game::Exiting;
     break;
   case MainMenu::Play:
	InstructionScreen instructionScreen;
	instructionScreen.Show(_mainWindow);
    ResetGame();
    _gameState = Game::Playing;
     break;
   case MainMenu::Music:
	 _gameState = Game::ShowingMenu;
	 if(ServiceLocator::GetAudio()->IsSongPlaying())
	 {
		ServiceLocator::GetAudio()->StopAllSounds();
	 }
	 break;
  }
}
void Game::ShowGameOverScreen()
{
  GameEndScreen gameEndScreen;
    gameEndScreen.ShowWin(_mainWindow);
	_gameState = ShowingMenu;
}  
void Game::ResetGame()
{
  std::vector<std::string> enemies;
  enemies.push_back("Enemy1");
  enemies.push_back("Enemy2");
  enemies.push_back("Enemy3");

  for(unsigned int i = 0; i < enemies.size(); i++)
  {
  AIShip* enemy = dynamic_cast<AIShip*>(Game::GetGameObjectManager().Get(enemies[i]));
	assert(NULL != enemy);
	
	enemy->setElapsedTime(0);
  }
  WeaponPowerUp* weapon = dynamic_cast<WeaponPowerUp*>(Game::GetGameObjectManager().Get("WeaponPowerUp"));
  assert(NULL != weapon);
  weapon->setPowerUpLevel(1);
  weapon->setElapsedTime(20.f);
  weapon->SetPosition(SCREEN_WIDTH/2, _gameField.Top - 100);
  
  ShieldPowerUp* shield = dynamic_cast<ShieldPowerUp*>(Game::GetGameObjectManager().Get("ShieldPowerUp"));
  assert(NULL != weapon);
  shield->setElapsedTime(10.f);
  shield->SetPosition(SCREEN_WIDTH/2, _gameField.Top - 100);
  _score = 0;

  Boss* boss = dynamic_cast<Boss*>(Game::GetGameObjectManager().Get("Boss"));
  assert(NULL != boss);
  boss->setElapsedTime(0.f);

   AILaser* laser1 = dynamic_cast<AILaser*>(Game::GetGameObjectManager().Get("AILaser1"));
  assert(NULL != laser1);
  laser1->setElapsedTime(0.f);
  laser1->setSpeed(0.f);
  laser1->SetPosition(SCREEN_WIDTH/2, _gameField.Top - 100);

  AILaser2* laser2 = dynamic_cast<AILaser2*>(Game::GetGameObjectManager().Get("AILaser2"));
  assert(NULL != laser2);
  laser2->setElapsedTime(0.f);
  laser2->setSpeed(0.f);
  laser2->SetPosition(SCREEN_WIDTH/2, _gameField.Top - 100);

  AILaser3* laser3 = dynamic_cast<AILaser3*>(Game::GetGameObjectManager().Get("AILaser3"));
  assert(NULL != laser3);
  laser3->setElapsedTime(0.f);
  laser3->setSpeed(0.f);
  laser3->SetPosition(SCREEN_WIDTH/2, _gameField.Top - 100);

  BossLaser* blaser = dynamic_cast<BossLaser*>(Game::GetGameObjectManager().Get("BossLaser"));
  assert(NULL != blaser);
  blaser->setElapsedTime(0.f);
  blaser->setSpeed(0.f,0.f);
  blaser->SetPosition(SCREEN_WIDTH/2, _gameField.Top - 100);




  
}
void Game::GameLoop()
{
  sf::Event currentEvent;
  _mainWindow.GetEvent(currentEvent);

  switch(_gameState)
  {
    case Game::ShowingSplash:
      {
        ShowSplashScreen();
        break;
      }
    case Game::ShowingMenu:
      {
        ShowMenu();
        break;
      }
    case Game::Playing:
      {
		
		_mainWindow.Clear(sf::Color(0,0,0));
        _gameObjectManager.UpdateAll();
        _gameObjectManager.DrawAll(_mainWindow);
        _gui.Draw(_mainWindow);
        _mainWindow.Display();

        if(currentEvent.Type == sf::Event::Closed)
        {
          _gameState = Game::Exiting;
        }
        if(currentEvent.Type == sf::Event::KeyPressed)
        {
          if(sf::Key::Escape == currentEvent.Key.Code)
          {
            ShowMenu();
          }
        }

        break;
      }
    case Game::GameOver:
      {
        ShowGameOverScreen();
        break;
      }
  }
}
void Game::gotHit()
{    
	ServiceLocator::GetAudio()->PlaySound("assets/Slave1-Seismic.wav");
	_gameState = Game::GameOver;
}
Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;
GameObjectManager Game::_gameObjectManager;
GUI Game::_gui;
sf::Rect<int> Game::_gameField(0, 50, SCREEN_WIDTH, SCREEN_HEIGHT - 25);
int Game::_score =  0;