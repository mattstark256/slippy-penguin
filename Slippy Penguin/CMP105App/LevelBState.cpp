#include "LevelBState.h"


LevelBState::LevelBState(GameData* _gameData, int _level) : LevelState(_gameData, _level)
{
	tilemapManager.generateTilemap("gfx/Levels/LevelB.png");

	player->setPosition(tileToPosition(12, 11));
	player->setFacingDirection(0);
	camera->jumpToTarget();

	fishManager->addFish(tileToPosition(11, 4), 3);
	fishManager->addFish(tileToPosition(3, 6), 0);
	fishManager->addFish(tileToPosition(16, 11), 0);
	fishManager->addFish(tileToPosition(17, 10), 1);

	sealManager->addSeal(tileToPosition(11.5, 8.5), tileToPosition(15.5, 8.5), 0.6, 4);
	sealManager->addSeal(tileToPosition(6, 7.5), tileToPosition(6, 4.5), 0.2, 3.5);
}


LevelBState::~LevelBState()
{
}