#include "LevelDState.h"


LevelDState::LevelDState(GameData* _gameData, int _level) : LevelState(_gameData, _level)
{
	tilemapManager.generateTilemap("gfx/Levels/LevelD.png");

	player->setPosition(tileToPosition(9, 15));
	player->setFacingDirection(2);
	camera->jumpToTarget();

	fishManager->addFish(tileToPosition(21, 16), 2);
	fishManager->addFish(tileToPosition(22, 15), 3);
	fishManager->addFish(tileToPosition(15, 10), 1);
	fishManager->addFish(tileToPosition(4, 6), 2);
	fishManager->addFish(tileToPosition(6, 5), 3);
	fishManager->addFish(tileToPosition(3, 9), 3);

	sealManager->addSeal(tileToPosition(9, 10), 24, 0.6, -5);
	sealManager->addSeal(tileToPosition(9, 10), 52, 0.4, 10);
	sealManager->addSeal(tileToPosition(9, 10), 52, 0.9, 10);
	sealManager->addSeal(tileToPosition(14, 15), 24, 0.0, 5);
	sealManager->addSeal(tileToPosition(17, 15), 24, 0.1, -5);
}


LevelDState::~LevelDState()
{
}