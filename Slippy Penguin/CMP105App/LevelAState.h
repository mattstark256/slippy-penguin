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
	sf::Texture arrowTexture;
	GameObject arrow;
};

