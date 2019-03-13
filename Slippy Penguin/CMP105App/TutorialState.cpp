#include "TutorialState.h"


TutorialState::TutorialState(GameData* gameData) : MenuState(gameData)
{
}


TutorialState::~TutorialState()
{
}


void TutorialState::handleInput(float dt)
{
}


void TutorialState::update(float dt)
{
}


void TutorialState::renderObjects()
{
	MenuState::renderObjects();
}
