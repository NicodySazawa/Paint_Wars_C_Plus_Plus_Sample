#include "instructionscreen.h"
#include "game.h"

void InstructionScreen::Show(sf::RenderWindow& window)
{
  window.Clear(sf::Color(0,0,0));

	sf::Image image;
	if(image.LoadFromFile("assets/Instructions.png") !=true)
	{
		return;
	}
	sf::Sprite sprite(image);
	window.Draw(sprite);
 

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