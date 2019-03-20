#pragma once
#include "State.h"

#include "TilemapManager.h"
#include "ParticleManager.h"
#include "Camera.h"
#include "Player.h"


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
	TilemapManager tilemapManager;
	ParticleManager particleManager;
	Camera* camera;
	Player* player;

	virtual void renderObjects();
	void win();
	void lose(std::string loseMessage);
	void openPauseMenu();
};

