#include "LevelAState.h"



LevelAState::LevelAState(GameData* _gameData, int _level) : LevelState(_gameData, _level)
{
	tilemapManager.generateTilemap("gfx/Levels/LevelA.png");

	player->setPosition(tileToPosition(13, 7));
	player->setFacingDirection(2);
	camera->jumpToTarget();

	fishManager->addFish(tileToPosition(8, 4), 0);
	fishManager->addFish(tileToPosition(15, 3), 1);
	fishManager->addFish(tileToPosition(16, 4), 2);
	fishManager->addFish(tileToPosition(12, 8), 1);

	//sealManager->addSeal(tileToPosition(7, 7), 32, 0.125, 6);
	//sealManager->addSeal(tileToPosition(12.5, 7), tileToPosition(12.5, 12), 0.25, 5);
	//sealManager->addSeal(tileToPosition(10, 9.5), tileToPosition(15, 9.5), 0, 5);
}


LevelAState::~LevelAState()
{
}