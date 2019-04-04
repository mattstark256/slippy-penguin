#pragma once
#include "LevelState.h"


class LevelAState :
	public LevelState
{
public:
	LevelAState(GameData* _gameData, int _level);
	~LevelAState();

	void renderUniqueLevelObjects();

private:
	// Level A has an arrow on the ice to hint that the player can slide diagonally.
	sf::Texture arrowTexture;
	GameObject arrow;
};

