#include "LevelCState.h"


LevelCState::LevelCState(GameData* _gameData, int _level) : LevelState(_gameData, _level)
{
	tilemapManager.generateTilemap("gfx/Levels/LevelC.png");

	player->setPosition(tileToPosition(8, 9.5));
	player->setFacingDirection(2);
	camera->jumpToTarget();

	fishManager->addFish(tileToPosition(9, 3), 3);
	fishManager->addFish(tileToPosition(11, 6), 0);
	fishManager->addFish(tileToPosition(12, 7), 1);

	sealManager->addSeal(tileToPosition(6.5, 6.5), 20, 0.6, 4);
}


LevelCState::~LevelCState()
{
}