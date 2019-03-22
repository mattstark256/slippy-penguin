#include "LevelAState.h"



LevelAState::LevelAState(GameData* _gameData, int _level) : LevelState(_gameData, _level)
{
	tilemapManager.generateTilemap("gfx/Levels/LevelA.png");

	player->setPosition(sf::Vector2f(13 * 16, 7 * 16));
	camera->jumpToTarget();

	fishManager->addFish(sf::Vector2i(8, 4), 0);
	fishManager->addFish(sf::Vector2i(15, 3), 1);
	fishManager->addFish(sf::Vector2i(16, 4), 2);
	fishManager->addFish(sf::Vector2i(7, 7), 0);
	fishManager->addFish(sf::Vector2i(13, 8), 0);
}


LevelAState::~LevelAState()
{
}


void LevelAState::handleInput(float dt)
{
	LevelState::handleInput(dt);
}


void LevelAState::update(float dt)
{
	LevelState::update(dt);
}


void LevelAState::renderObjects()
{
	LevelState::renderObjects();
}
