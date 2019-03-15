#pragma once
#include "LevelState.h"


class LevelAState :
	public LevelState
{
public:
	LevelAState(GameData* _gameData, int _level);
	~LevelAState();

	virtual void handleInput(float dt);
	virtual void update(float dt);

protected:
	virtual void renderObjects();
};

