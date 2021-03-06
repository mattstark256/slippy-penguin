#pragma once
#include "MenuState.h"

#include "Button.h"


// This is the main menu the user will see on starting the application
class MainMenuState :
	public MenuState
{
public:
	MainMenuState(GameData* _gameData);
	~MainMenuState();

	virtual void handleInput(float dt);
	virtual void update(float dt);

protected:
	virtual void renderObjects();

private:
	sf::Text textTitle;
	Button* newGameButton;
	Button* continueButton;
	Button* creditsButton;
	Button* quitButton;
};

