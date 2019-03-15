#pragma once
#include "MenuState.h"

#include "Button.h"


// This is the screen the player sees before starting a level
class PreLevelState :
	public MenuState
{
public:
	PreLevelState(GameData* gameData, int _level);
	~PreLevelState();

	virtual void handleInput(float dt);
	virtual void update(float dt);

protected:
	virtual void renderObjects();

private:
	int level;

	sf::Text textTitle;
	Button* buttonStart;
};

