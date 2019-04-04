#pragma once
#include "MenuState.h"

#include "Button.h"


// This is the screen the player sees if they lose a level
class LoseState :
	public MenuState
{
public:
	LoseState(GameData* _gameData, int _level, std::string loseMessage);
	~LoseState();

	virtual void handleInput(float dt);
	virtual void update(float dt);

protected:
	virtual void renderObjects();

private:
	int level;

	sf::Text textTitle;
	sf::Text textMessage;
	Button* buttonRetry;
	Button* buttonQuit;
};

