#include "MenuState.h"



MenuState::MenuState(GameData* _gameData) : State(_gameData)
{
	rectangle.setSize(sf::Vector2f(400, 200));
	rectangle.setFillColor(sf::Color::Red);
}


MenuState::~MenuState()
{
}


void MenuState::handleInput(float dt)
{
	State::handleInput(dt);
}


void MenuState::update(float dt)
{
	State::update(dt);
}


void MenuState::renderObjects()
{
	State::renderObjects();

	gameData->window->draw(rectangle);
}
