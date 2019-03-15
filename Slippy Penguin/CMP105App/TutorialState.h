#pragma once
#include "MenuState.h"

#include "Button.h"


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

	sf::Text textTitle;
	sf::Text textInstruction1;
	Button* startButton;
};

