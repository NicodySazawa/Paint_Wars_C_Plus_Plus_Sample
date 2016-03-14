#ifndef GAME_END_SCREEN_H
#define GAME_END_SCREEN_H

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

class GameEndScreen
{
public:
  GameEndScreen();
  ~GameEndScreen();

  void ShowWin(sf::RenderWindow& window);

private:

  void DrawBacking(sf::RenderWindow& window);
};

#endif
