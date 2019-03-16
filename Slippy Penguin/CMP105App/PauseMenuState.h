#pragma once
#include "MenuState.h"

#include "Button.h"


class PauseMenuState :
	public MenuState
{
public:
	PauseMenuState(GameData* _gameData, int _level, int score, int targetScore);
	~PauseMenuState();

	virtual void handleInput(float dt);
	virtual void update(float dt);

protected:
	virtual void renderObjects();

private:
	int level;

	sf::Text textTitle;
	sf::Text textScore;
	Button* buttonResume;
	Button* buttonRestart;
	Button* buttonQuit;
};

