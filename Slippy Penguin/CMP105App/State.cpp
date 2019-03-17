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
	windowCentre = (sf::Vector2f)gameData->window->getSize() * 0.5f;
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


// Used for restoring the default view (0,0 at top left, 1 pixel per pixel).
// It should be called after any view changes.
// SFML's getDefaultView() function isn't suitable because it doesn't update when the player resizes the window.
void State::resetView()
{
	gameData->window->setView(
		sf::View((sf::Vector2f)gameData->window->getSize() * 0.5f, // centre
		(sf::Vector2f)gameData->window->getSize())); // size
}
