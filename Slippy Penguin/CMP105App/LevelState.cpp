#include "LevelState.h"

#include "WinState.h"
#include "FinalWinState.h"
#include "LoseState.h"
#include "LevelLoader.h"
#include "PauseMenuState.h"
#include <iostream>


LevelState::LevelState(GameData* _gameData, int _level) : State(_gameData), level(_level)
{
	camera = new Camera(gameData);
	sealManager = new SealManager(gameData, camera, &particleManager);
	fishManager = new FishManager(gameData);
	player = new Player(gameData, this, &tilemapManager, &particleManager, fishManager, sealManager);
	camera->setSubject(player);

	gameData->audioManager->getMusic()->play();
}


LevelState::~LevelState()
{
}


void LevelState::handleInput(float dt)
{
	// This can't just be in the constructor because that would mean opening and closing the pause menu would leave the mouse visible
	gameData->window->setMouseCursorVisible(false);

	State::handleInput(dt);

	player->handleInput(dt);

	// + and - can be used to skip to the win and lose screens respectively. This is for testing and demonstration purposes.
	if (gameData->input->isKeyDown(sf::Keyboard::Add))
	{
		win();
	}
	if (gameData->input->isKeyDown(sf::Keyboard::Subtract))
	{
		lose("You pressed the lose key!");
	}

	// Esc can be used to pause the game
	if (gameData->input->isKeyDown(sf::Keyboard::Escape))
	{
		gameData->input->setKeyUp(sf::Keyboard::Escape);
		openPauseMenu();
	}
}


void LevelState::update(float dt)
{
	State::update(dt);

	particleManager.update(dt);
	camera->update(dt);
	player->update(dt);
	fishManager->update(dt);
	sealManager->update(dt);
	tilemapManager.animateTiles(dt);
	fallingSnow.update(dt);
}


void LevelState::renderObjects()
{
	State::renderObjects();

	// Set up camera space rendering
	gameData->window->setView(camera->getCameraView());

	tilemapManager.render(gameData->window);
	renderUniqueLevelObjects();
	fishManager->render();
	particleManager.render(gameData->window);
	sealManager->render();
	player->render();
	fallingSnow.render(gameData->window);

	// Set up screen space rendering
	resetView();

	fishManager->renderUI();
}


// This is overridden by derived classes.
void LevelState::renderUniqueLevelObjects()
{
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
	gameData->stateManager->pushState(new PauseMenuState(gameData, level, fishManager->getFishEaten(), fishManager->getInitialFishCount(), this));
}


// This is a helper function for converting tile coordinates to world coordinates
sf::Vector2f LevelState::tileToPosition(float x, float y)
{
	return sf::Vector2f(x * 16 + 8, y * 16 + 8);
}
