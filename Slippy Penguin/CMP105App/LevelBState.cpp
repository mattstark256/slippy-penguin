#include "LevelBState.h"



LevelBState::LevelBState(GameData* _gameData, int _level) : LevelState(_gameData, _level)
{
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
