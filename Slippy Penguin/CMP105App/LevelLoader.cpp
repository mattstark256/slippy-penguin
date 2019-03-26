#include "LevelLoader.h"

#include "LevelAState.h"
#include "LevelBState.h"
#include "LevelCState.h"
#include "LevelDState.h"
#include "LevelEState.h"
#include <iostream>


LevelLoader::LevelLoader()
{
}


LevelLoader::~LevelLoader()
{
}


// Creates a level and returns a pointer to it. Which level is created is dependent on levelNumber.
LevelState* LevelLoader::loadLevel(int levelNumber, GameData* gameData)
{
	LevelState* levelState = nullptr;

	switch (levelNumber)
	{
	case 1:
		levelState = new LevelAState(gameData, levelNumber);
		break;
	case 2:
		levelState = new LevelBState(gameData, levelNumber);
		break;
	case 3:
		levelState = new LevelCState(gameData, levelNumber);
		break;
	case 4:
		levelState = new LevelEState(gameData, levelNumber);
		break;
	case 5:
		levelState = new LevelDState(gameData, levelNumber);
		break;
	default:
		std::cout << "Levelloader::loadLevel couldn't find level number ";
		std::cout << levelNumber;
		std::cout << " so returned nullptr! This must never happen!";
		break;
	}

	return levelState;
}


// This is used for checking whether the player has completed the game.
bool LevelLoader::isFinalLevel(int levelNumber)
{
	return levelNumber == 5;
}
