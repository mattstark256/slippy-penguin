#include "LevelAState.h"



LevelAState::LevelAState(GameData* _gameData, int _level) : LevelState(_gameData, _level)
{
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
