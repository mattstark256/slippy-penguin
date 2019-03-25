#include "LevelBState.h"



LevelBState::LevelBState(GameData* _gameData, int _level) : LevelState(_gameData, _level)
{
	tilemapManager.generateTilemap("gfx/Levels/LevelB.png");

	player->setPosition(tileToPosition(5, 10));
	player->setFacingDirection(0);
	camera->jumpToTarget();

	fishManager->addFish(tileToPosition(5, 14), 3);
	fishManager->addFish(tileToPosition(14, 12), 0);
	fishManager->addFish(tileToPosition(9, 9), 0);
	fishManager->addFish(tileToPosition(10, 8), 1);

	sealManager->addSeal(tileToPosition(8.5, 11), tileToPosition(8.5, 14), 0.1, 4);
	sealManager->addSeal(tileToPosition(5, 6.5), tileToPosition(9, 6.5), 0.8, 4);
}


LevelBState::~LevelBState()
{
}


void LevelBState::handleInput(float dt)
{
	LevelState::handleInput(dt);
}


void LevelBState::update(float dt)
{
	LevelState::update(dt);
}


void LevelBState::renderObjects()
{
	LevelState::renderObjects();
}
