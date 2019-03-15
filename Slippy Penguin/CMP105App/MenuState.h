#pragma once
#include "State.h"


// This is the base class for all menu screens. This means if I want them to all have the same background or something I can do it here.
class MenuState :
	public State
{
public:
	MenuState(GameData* _gameData);
	~MenuState();

	virtual void handleInput(float dt);
	virtual void update(float dt);

protected:
	virtual void renderObjects();

private:
	sf::RectangleShape rectangle;
};

