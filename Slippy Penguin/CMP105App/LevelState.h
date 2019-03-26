#pragma once
#include "State.h"

#include "TilemapManager.h"
#include "ParticleManager.h"
#include "FishManager.h"
#include "SealManager.h"
#include "Camera.h"
#include "Player.h"
#include "FallingSnow.h"


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
	FallingSnow fallingSnow;

	virtual void renderObjects();
	void openPauseMenu();

	// This is used so that levels can have unique objects that are rendered at an appropriate point in the pipeline, ie in front of the tilemap but behind falling snow.
	virtual void renderUniqueLevelObjects();

	sf::Vector2f tileToPosition(float x, float y);
};

