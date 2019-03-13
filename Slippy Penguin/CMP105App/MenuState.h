#pragma once
#include "State.h"


// This is the base class for all menu screens.
class MenuState :
	public State
{
public:
	MenuState(GameData* gameData);
	~MenuState();

	virtual void handleInput(float dt);
	virtual void update(float dt);

protected:
	virtual void renderObjects();

private:
	sf::RectangleShape rectangle;
};

