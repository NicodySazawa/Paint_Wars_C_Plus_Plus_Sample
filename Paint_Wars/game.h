#ifndef GAME_H
#define GAME_H

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <cassert>
#include "gameobjectmanager.h"
#include "gui.h"
#include "gameendscreen.h"

class Game
{

public:
  const static int SCREEN_WIDTH = 1024;
  const static int SCREEN_HEIGHT = 768;

  static void Start();
  static sf::RenderWindow& GetWindow();
  const static sf::Input& GetInput();
  static GameObjectManager& GetGameObjectManager();
  const static sf::Rect<int> GetGameField();
  static void SetScore(int);
  static int GetScore();
  static void ShowGameOverScreen();
  static void gotHit();
 private:
    enum GameState {
    Uninitialized,
    ShowingSplash,
    Paused,
    ShowingMenu,
    Playing,
    GameOver,
    Exiting
  };
  static GameState _gameState;
  static void ShowMenu();
  static sf::RenderWindow _mainWindow;
  static GameObjectManager _gameObjectManager;
  static GUI _gui;
  static sf::Rect<int> _gameField;
  static int _score;

  static bool IsExiting();
  static void GameLoop();
  static void ShowSplashScreen();
  static void ResetGame();
};
#endif
