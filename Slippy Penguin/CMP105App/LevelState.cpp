#include "LevelState.h"

#include "WinState.h"
#include "FinalWinState.h"
#include "LoseState.h"
#include "LevelLoader.h"
#include "PauseMenuState.h"
#include <iostream>


LevelState::LevelState(GameData* _gameData, int _level) : State(_gameData), level(_level)
{
	player = new Player(gameData, &tilemapManager);
	camera = new Camera(gameData);
	camera->setSubject(player);
}


LevelState::~LevelState()
{
}


void LevelState::handleInput(float dt)
{
	State::handleInput(dt);

	player->handleInput(dt);

	// These are for testing purposes and should be disabled before the game is finished.
	if (gameData->input->isKeyDown(sf::Keyboard::Num1))
	{
		win();
	}
	if (gameData->input->isKeyDown(sf::Keyboard::Num2))
	{
		lose("You pressed the lose key!");
	}

	if (gameData->input->isKeyDown(sf::Keyboard::Escape))
	{
		gameData->input->setKeyUp(sf::Keyboard::Escape);
		openPauseMenu();
	}
}


void LevelState::update(float dt)
{
	State::update(dt);

	camera->update(dt);
	player->update(dt);
}


void LevelState::renderObjects()
{
	State::renderObjects();

	// Set up camera space rendering
	gameData->window->setView(camera->getCameraView());

	tilemapManager.render(gameData->window);
	gameData->window->draw(*player);

	resetView();
}


void LevelState::win()
{

	if (LevelLoader::isFinalLevel(level))
	{
		gameData->playerData->resetCompletedLevels();
		gameData->stateManager->replaceState(new FinalWinState(gameData, level));
	}
	else
	{
		gameData->playerData->updateCompletedLevels(level);
		gameData->stateManager->replaceState(new WinState(gameData, level));
	}
}


void LevelState::lose(std::string loseMessage)
{
	gameData->stateManager->replaceState(new LoseState(gameData, level, loseMessage));
}


void LevelState::openPauseMenu()
{
	gameData->stateManager->pushState(new PauseMenuState(gameData, level, 1, 3));
}
