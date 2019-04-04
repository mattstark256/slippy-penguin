#pragma once
#include "State.h"


// This is the base class for all menu screens. They all have the same background.
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
	sf::Sprite wallpaper;
	sf::Texture texture;
};

