#pragma once

#include "GameData.h"


// This is a base class for all of the application's states, including menus and levels.
class State
{
public:
	State(GameData* _gameData);
	~State();

	virtual void handleInput(float dt);
	virtual void update(float dt);
	void render();

protected:
	GameData* gameData;

	virtual void renderObjects();

private:
	// Default functions for rendering to the screen.
	void beginDraw();
	void endDraw();
};

