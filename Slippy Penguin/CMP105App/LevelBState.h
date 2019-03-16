#pragma once
#include "LevelState.h"


class LevelBState :
	public LevelState
{
public:
	LevelBState(GameData* _gameData, int _level);
	~LevelBState();

	virtual void handleInput(float dt);
	virtual void update(float dt);

protected:
	virtual void renderObjects();
};

