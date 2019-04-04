#pragma once
#include "MenuState.h"

#include "Button.h"


// This is the screen showing who made the font, music etc.
class CreditsState :
	public MenuState
{
public:
	CreditsState(GameData* _gameData);
	~CreditsState();

	virtual void handleInput(float dt);
	virtual void update(float dt);

protected:
	virtual void renderObjects();

private:
	sf::Text textTitle;
	sf::Text textCredit1;
	Button* mainMenuButton;
};

