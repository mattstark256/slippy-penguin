#pragma once
#include "MenuState.h"

#include "Button.h"


// This is the screen the player sees if they win a level (that isn't the final level)
class WinState :
	public MenuState
{
public:
	WinState(GameData* gameData, int _level);
	~WinState();

	virtual void handleInput(float dt);
	virtual void update(float dt);

protected:
	virtual void renderObjects();

private:
	int level;

	sf::Text textTitle;
	Button* buttonContinue;
};

