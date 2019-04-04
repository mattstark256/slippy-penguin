#pragma once
#include "State.h"

#include "Button.h"
#include "LevelState.h"


// This is the state that is loaded when the player pauses the game. It doesn't inherit from MenuState because instead of using the menu background it renders the paused level behind it.
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
	LevelState* pausedLevel;
	sf::RectangleShape menuBackground;
	sf::Texture backgroundTexture;
};

