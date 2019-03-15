#include "LevelState.h"

#include "WinState.h"
#include "LoseState.h"


LevelState::LevelState(GameData* _gameData, int _level) : State(_gameData), level(_level)
{
}


LevelState::~LevelState()
{
}


void LevelState::handleInput(float dt)
{
	State::handleInput(dt);

	if (gameData->input->isKeyDown(sf::Keyboard::Num1))
	{
		win();
	}
	if (gameData->input->isKeyDown(sf::Keyboard::Num2))
	{
		lose("You pressed the lose button!");
	}
}


void LevelState::update(float dt)
{
	State::update(dt);
}


void LevelState::renderObjects()
{
	State::renderObjects();
}


void LevelState::win()
{
	gameData->stateManager->replaceState(new WinState(gameData, level));
}


void LevelState::lose(std::string loseMessage)
{
	gameData->stateManager->replaceState(new LoseState(gameData, level, loseMessage));
}
