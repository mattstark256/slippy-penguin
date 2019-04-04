#pragma once
#include "State.h"

#include "TilemapManager.h"
#include "ParticleManager.h"
#include "FishManager.h"
#include "SealManager.h"
#include "Camera.h"
#include "Player.h"
#include "FallingSnow.h"


// This is the base class for all game levels.
class LevelState :
	public State
{
public:
	LevelState(GameData* _gameData, int _level);
	~LevelState();

	virtual void handleInput(float dt);
	virtual void update(float dt);
	virtual void renderObjects();

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

	void openPauseMenu();

	// This is used so that levels can have unique objects that are rendered at an appropriate point in the pipeline, ie in front of the tilemap but behind falling snow.
	virtual void renderUniqueLevelObjects();

	sf::Vector2f tileToPosition(float x, float y);
};

