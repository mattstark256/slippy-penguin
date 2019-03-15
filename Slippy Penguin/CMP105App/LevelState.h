#pragma once
#include "State.h"


class LevelState :
	public State
{
public:
	LevelState(GameData* _gameData, int _level);
	~LevelState();

	virtual void handleInput(float dt);
	virtual void update(float dt);

protected:
	int level;

	virtual void renderObjects();
	void win();
	void lose(std::string loseMessage);
};

