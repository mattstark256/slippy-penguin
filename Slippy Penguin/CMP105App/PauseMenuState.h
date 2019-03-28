#pragma once
#include "State.h"

#include "Button.h"
#include "LevelState.h"


class PauseMenuState :
	public State
{
public:
	PauseMenuState(GameData* _gameData, int _level, int score, int targetScore, LevelState* _pausedLevel);
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
	sf::RectangleShape menuBackground;
	LevelState* pausedLevel;
};

