#include "State.h"



State::State(GameData* _gameData) : gameData(_gameData)
{
}


State::~State()
{
}


// handle user input
void State::handleInput(float dt)
{
}

// Update game objects
void State::update(float dt)
{
}

// Render level
void State::render()
{
	beginDraw();

	renderObjects();

	endDraw();
}


// This is overridden by child classes of State.
void State::renderObjects()
{
}


// Begins rendering to the back buffer. Background colour set to light blue.
void State::beginDraw()
{
	gameData->window->clear(sf::Color(25, 57, 119));
}

// Ends rendering to the back buffer, and swaps buffer to the screen.
void State::endDraw()
{
	gameData->window->display();
}