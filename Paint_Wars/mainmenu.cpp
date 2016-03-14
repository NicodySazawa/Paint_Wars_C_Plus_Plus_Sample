#include "mainmenu.h"
#include "servicelocator.h"
MainMenu::MainMenu()
{
}
MainMenu::~MainMenu()
{
}
MainMenu::MenuResult MainMenu::Show(sf::RenderWindow& window)
{
   window.Clear(sf::Color(0,0,0));

  MenuItem playButton;
  playButton.rect.Top = 768 / 2 - 100;
  playButton.rect.Bottom = 768 / 2 ;
  playButton.rect.Left = 1024 / 3;
  playButton.rect.Right = 1024 / 3 * 2;
  playButton.action = Play;

  MenuItem exitButton;
  exitButton.rect.Top = 768 / 2;
  exitButton.rect.Bottom = 768 / 2 + 100;
  exitButton.rect.Left = 1024 / 3;
  exitButton.rect.Right = 1024 / 3 * 2;
  exitButton.action = Exit;

  MenuItem musicButton;
  musicButton.rect.Top = 768 / 2 + 100;
  musicButton.rect.Bottom = 768 / 2 + 200;
  musicButton.rect.Left = 1024 / 3;
  musicButton.rect.Right = 1024 / 3 * 2;
  musicButton.action = Music;
  
  _menuItems.push_back(playButton);
  _menuItems.push_back(exitButton);
  _menuItems.push_back(musicButton);

  window.Clear(sf::Color(0,0,0));

  	sf::Image image;
	image.LoadFromFile("assets/Earthpaint.png");
	sf::Sprite sprite(image);
	window.Draw(sprite);

  sf::Shape playRect = sf::Shape::Rectangle(
    playButton.rect.Left * 1.f,
    playButton.rect.Top * 1.f,
    playButton.rect.Right * 1.f,
    playButton.rect.Bottom * 1.f,
    sf::Color::White, true, sf::Color::White
  );
  playRect.EnableFill(false);
  window.Draw(playRect);
  
  sf::Shape exitRect = sf::Shape::Rectangle(
    exitButton.rect.Left * 1.f,
    exitButton.rect.Top * 1.f,
    exitButton.rect.Right * 1.f,
    exitButton.rect.Bottom * 1.f,
    sf::Color::White, true, sf::Color::White
  );
  exitRect.EnableFill(false);
  window.Draw(exitRect);

  sf::Shape musicRect = sf::Shape::Rectangle(
	  musicButton.rect.Left * 1.f,
	  musicButton.rect.Top * 1.f,
	  musicButton.rect.Right * 1.f,
	  musicButton.rect.Bottom * 1.f,
	  sf::Color::White, true, sf::Color::White
  );
  musicRect.EnableFill(false);
  window.Draw(musicRect);

  sf::String playLabel = sf::String("Start Game");
  playLabel.SetPosition(1024 / 2 - 90, playButton.rect.Top + 30);
  window.Draw(playLabel);
  
  sf::String exitLabel = sf::String("Exit Game");
  exitLabel.SetPosition(1024 / 2 - 90, exitButton.rect.Top + 30);
  window.Draw(exitLabel);

  sf::String musicLabel = sf::String("Mute Music");
  musicLabel.SetPosition(1024 / 2 - 90, musicButton.rect.Top + 30);
  window.Draw(musicLabel);

  window.Display();

  return GetMenuResponse(window);
}
MainMenu::MenuResult MainMenu::GetMenuResponse(sf::RenderWindow& window)
{
  sf::Event menuEvent;
  while(true)
  {
    while(window.GetEvent(menuEvent))
    {
      if (menuEvent.Type == sf::Event::MouseButtonPressed)
      {
        return HandleClick(menuEvent.MouseButton.X, menuEvent.MouseButton.Y);
      }
      if (menuEvent.Type == sf::Event::Closed)
      {
        return Exit;
      }
    }
  }
}

MainMenu::MenuResult MainMenu::HandleClick(int x, int y)
{
  std::list<MenuItem>::iterator it;
  for (it = _menuItems.begin(); it != _menuItems.end(); it++)
  {
    sf::Rect<int> menuItemRect = (*it).rect;
    if (menuItemRect.Bottom > y && menuItemRect.Top < y &&
        menuItemRect.Left < x && menuItemRect.Right > x)
    {
      return (*it).action;
    }
  }
  return Nothing;
}
const sf::Color sf::Color::White;