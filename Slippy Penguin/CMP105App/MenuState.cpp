#include "MenuState.h"



MenuState::MenuState(GameData* gameData) : State(gameData)
{
	rectangle.setSize(sf::Vector2f(400, 200));
	rectangle.setFillColor(sf::Color::Red);
}


MenuState::~MenuState()
{
}


void MenuState::handleInput(float dt)
{
}


void MenuState::update(float dt)
{
}


void MenuState::renderObjects()
{
	gameData->window->draw(rectangle);
}
