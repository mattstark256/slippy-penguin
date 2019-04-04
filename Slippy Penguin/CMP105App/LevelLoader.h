#pragma once

#include "LevelState.h"
#include "GameData.h"


// This class is used so that level states can be loaded by level number.
// This should be only place in the project where level states and level numbers are associated. In other words, in order to change the order or number of levels, this should be the only class that must be modified.
class LevelLoader
{
public:
	LevelLoader();
	~LevelLoader();

	static LevelState* loadLevel(int levelNumber, GameData* gameData);
	static bool isFinalLevel(int levelNumber);
};

