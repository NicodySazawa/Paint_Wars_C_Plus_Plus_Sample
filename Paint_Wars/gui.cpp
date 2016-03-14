#include <sstream>
#include "gui.h"
#include "game.h"
#include "playership.h"
#include <iostream>

GUI::GUI()
{
}

GUI::~GUI()
{
}

void GUI::Draw(sf::RenderWindow& window)
{
  
  std::ostringstream scoreout;
  scoreout << "Score: " << Game::GetScore();

  // dereference the pointer to get the actual object
  sf::String score(scoreout.str());
  
  window.Draw(score);

  sf::Rect<int> gameField = Game::GetGameField();
  window.Draw(sf::Shape::Line(
    gameField.Left, gameField.Top,
    gameField.Right, gameField.Top,
    2, sf::Color::White
  ));
  window.Draw(sf::Shape::Line(
    gameField.Left, gameField.Bottom,
    gameField.Right, gameField.Bottom,
    2, sf::Color::White
  ));
}
