#include "Game.h"
#include "MainMenu.h"
#include "SplashScreen.h"
#include "gameOptions.h"

void Game::Start(void)
{
	if (_gameState != Uninitialized)
		return;

	_mainWindow.create(sf::VideoMode(1024, 768, 32), "Pang!");
	
	_player1.Load("images/paddle.png");
	_player1.SetPosition((1024 / 2) - 45, 700);
	
	_gameState = Game::ShowingSplash;

	while (!IsExiting())
	{
		GameLoop();
	}

	_mainWindow.close();
}

bool Game::IsExiting()
{
	if (_gameState == Game::Exiting)
		return true;
	else
		return false;
}

void Game::GameLoop()
{
	sf::Event currentEvent;
	while (_mainWindow.pollEvent(currentEvent))
	{

		switch (_gameState)
		{
		case Game::ShowingMenu:
		{
							  ShowMenu();
							  break;
		}
		case Game::Playing:
		{
							  _mainWindow.clear(sf::Color(0, 0, 0, 0));
							  _mainWindow.display();
							  _player1.Draw(_mainWindow);

							  if (currentEvent.type == sf::Event::Closed)
							  {
								  _gameState = Game::Exiting;
							  }
							  break;
		}
		case Game::ShowingSplash:
		{
							ShowSplashScreen();
							break;
		}
		case Game::Options:
							gOptions();
							_gameState = Game::Options;
							break;
		}
	}
}

void Game::ShowSplashScreen()
 {
	   SplashScreen splashScreen;
	   SplashScreen splashScreen2;

	   splashScreen.Show(_mainWindow);
	   splashScreen2.Show2(_mainWindow);

	   _gameState = Game::ShowingMenu;
 }

void Game::ShowMenu()
{
	MainMenu mainMenu;
	MainMenu::MenuResult result = mainMenu.Show(_mainWindow);
	switch (result)
	{
	case MainMenu::Exit:
		_gameState = Game::Exiting;
		break;
	case MainMenu::Play:
		_gameState = Game::Playing;
		break;
	case MainMenu::Options:
		_gameState = Game::Options;
	}
}

void Game::gOptions()
{
	GameOptions optionsMenu;
	optionsMenu.ShowOptions(_mainWindow);
	_gameState = Game::ShowingMenu;
}

Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;
PlayerPaddle Game::_player1;