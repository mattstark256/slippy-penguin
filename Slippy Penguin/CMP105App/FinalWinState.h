#pragma once
#include "MenuState.h"

#include "Button.h"


// This is the screen the player sees if they win the final level
class FinalWinState :
	public MenuState
{
public:
	FinalWinState(GameData* _gameData, int _level);
	~FinalWinState();

	virtual void handleInput(float dt);
	virtual void update(float dt);

protected:
	virtual void renderObjects();

private:
	int level;

	sf::Text textTitle;
	sf::Text textMessage;
	Button* buttonContinue;
};

