#include "gameendscreen.h"
#include "game.h"
#include <sstream>
using namespace sf;

GameEndScreen::GameEndScreen()
{
}

GameEndScreen::~GameEndScreen()
{
}

void GameEndScreen::ShowWin(sf::RenderWindow& window)
{
  DrawBacking(window);
    sf::Image image;
	image.LoadFromFile("assets/Spaceshippaint.png");
	sf::Sprite sprite(image);
	window.Draw(sprite);
   std::ostringstream endScore;
   sf::String gameOver = sf::String("Game Over!");
   sf::String instructions = sf::String("Click Or Press Any Key To Return To Main Menu");
   endScore << "Your Score: " << Game::GetScore();
   sf::String msg = sf::String(endScore.str());
   gameOver.SetSize(72.f);
   gameOver.SetPosition(Game::SCREEN_WIDTH / 2 - 250,
   Game::GetGameField().Top - 20);
   instructions.SetSize(36.f);
   instructions.SetPosition(150, Game::SCREEN_HEIGHT / 2);
   msg.SetSize(72.f);
   msg.SetPosition(
   Game::SCREEN_WIDTH / 2 - 250,
   Game::SCREEN_HEIGHT - 150
  );
  window.Draw(msg);
  window.Draw(instructions);
  window.Draw(gameOver);
  window.Display();

  sf::Event event;
  while(true)
  {
    while(window.GetEvent(event))
    {
      if(event.Type == sf::Event::KeyPressed ||
         event.Type == sf::Event::MouseButtonPressed ||
         event.Type == sf::Event::Closed)
      {
        return;
      }
    }
  }
}

void GameEndScreen::DrawBacking(sf::RenderWindow& window)
{
  sf::Color transparentBlack = sf::Color(
    0, 0, 0, 255 * 1
  );
  window.Draw(sf::Shape::Rectangle(
    0, 0,
    Game::SCREEN_WIDTH, Game::SCREEN_HEIGHT,transparentBlack
  ));
}