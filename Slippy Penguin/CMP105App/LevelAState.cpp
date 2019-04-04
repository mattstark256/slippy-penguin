#include "LevelAState.h"

#include <iostream>
#define ARROW_TEXTURE_FILE_PATH "gfx/Arrow.png"


LevelAState::LevelAState(GameData* _gameData, int _level) : LevelState(_gameData, _level)
{
	tilemapManager.generateTilemap("gfx/Levels/LevelA.png");

	player->setPosition(tileToPosition(13, 6.3));
	player->setFacingDirection(2);
	camera->jumpToTarget();

	fishManager->addFish(tileToPosition(8, 4), 0);
	fishManager->addFish(tileToPosition(15, 3), 1);
	fishManager->addFish(tileToPosition(16, 4), 2);
	fishManager->addFish(tileToPosition(12, 8), 1);

	if (!arrowTexture.loadFromFile(ARROW_TEXTURE_FILE_PATH))
	{
		std::cout << "Unable to load " << ARROW_TEXTURE_FILE_PATH << std::endl;
	}
	arrow.setTexture(&arrowTexture);
	arrow.setPosition(tileToPosition(4.5, 5.5));
	arrow.setSize((sf::Vector2f)arrowTexture.getSize());
}


LevelAState::~LevelAState()
{
}


void LevelAState::renderUniqueLevelObjects()
{
	gameData->window->draw(arrow);
}


