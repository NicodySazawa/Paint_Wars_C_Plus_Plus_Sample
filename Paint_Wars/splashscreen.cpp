#include "SplashScreen.h"
#include "game.h"
void SplashScreen::Show(sf::RenderWindow& window)
{
  window.Clear(sf::Color(0,0,0));

	sf::Image image;
	if(image.LoadFromFile("assets/paint-wars.png") !=true)
	{
		return;
	}
	sf::Sprite sprite(image);
	window.Draw(sprite);
	

	sf::String inst = sf::String("Press any key or click the mouse to continue.");
	inst.SetPosition(
    Game::SCREEN_WIDTH / 2 - 300,
    Game::SCREEN_HEIGHT / 2 
  );
  window.Draw(inst);

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
