#include "Level.h"

#include <vector>

Level::Level(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;

	// initialise game objects
	button.setText("Start game");
	button.setInput(input);
}

Level::~Level()
{

}

// handle user input
void Level::handleInput(float dt)
{
	button.handleInput(dt);
}

// Update game objects
void Level::update(float dt)
{
	button.setPosition((sf::Vector2f)window->getSize() * 0.5f);

	if (button.wasPressed())
	{
		std::cout << "button pressed\n";
	}
}

// Render level
void Level::render()
{
	beginDraw();

	button.render(window);

	endDraw();
}

// Begins rendering to the back buffer. Background colour set to light blue.
void Level::beginDraw()
{
	window->clear(sf::Color(25, 57, 119));
}

// Ends rendering to the back buffer, and swaps buffer to the screen.
void Level::endDraw()
{
	window->display();
}