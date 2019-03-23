#pragma once
#include "State.h"

#include "TilemapManager.h"
#include "ParticleManager.h"
#include "FishManager.h"
#include "SealManager.h"
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

	void win();
	void lose(std::string loseMessage);

protected:
	int level;
	TilemapManager tilemapManager;
	ParticleManager particleManager;
	FishManager* fishManager;
	SealManager* sealManager;
	Camera* camera;
	Player* player;

	virtual void renderObjects();
	void openPauseMenu();

	sf::Vector2f tileToPosition(float x, float y);
};

