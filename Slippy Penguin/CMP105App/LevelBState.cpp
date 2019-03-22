#include "LevelBState.h"



LevelBState::LevelBState(GameData* _gameData, int _level) : LevelState(_gameData, _level)
{
	tilemapManager.generateTilemap("gfx/Levels/LevelTest.png");

	player->setPosition(sf::Vector2f(13 * 16, 7 * 16));
	camera->jumpToTarget();
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
