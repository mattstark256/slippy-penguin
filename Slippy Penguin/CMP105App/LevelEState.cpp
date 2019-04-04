#include "LevelEState.h"


LevelEState::LevelEState(GameData* _gameData, int _level) : LevelState(_gameData, _level)
{
	tilemapManager.generateTilemap("gfx/Levels/LevelE.png");

	player->setPosition(tileToPosition(13, 12));
	player->setFacingDirection(2);
	camera->jumpToTarget();

	fishManager->addFish(tileToPosition(4, 10), 3);
	fishManager->addFish(tileToPosition(14, 9), 0);
	fishManager->addFish(tileToPosition(19, 2), 1);
	fishManager->addFish(tileToPosition(21, 3), 2);

	sealManager->addSeal(tileToPosition(8.5, 6.5), tileToPosition(8.5, 11.5), 0, 5);
	sealManager->addSeal(tileToPosition(10.5, 6.5), tileToPosition(10.5, 11.5), 0.5, 5);

	sealManager->addSeal(tileToPosition(14.5, 4.5), tileToPosition(18.5, 4.5), 0, 4);
	sealManager->addSeal(tileToPosition(14.5, 6.5), tileToPosition(18.5, 6.5), 0.5, 4);
}


LevelEState::~LevelEState()
{
}