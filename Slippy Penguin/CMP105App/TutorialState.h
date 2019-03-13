#pragma once
#include "MenuState.h"


// This is the screen where the player sees instructions on how to play
class TutorialState :
	public MenuState
{
public:
	TutorialState(GameData* gameData);
	~TutorialState();

	virtual void handleInput(float dt);
	virtual void update(float dt);

protected:
	virtual void renderObjects();
};

