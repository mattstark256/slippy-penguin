#include "MenuState.h"

#include <iostream>
#include <math.h> // fmod

#define WALLPAPER_TEXTURE_FILE_PATH "gfx/Wallpaper.png"
#define WALLPAPER_SCALE 6


MenuState::MenuState(GameData* _gameData) : State(_gameData)
{
	gameData->window->setMouseCursorVisible(true);

	rectangle.setSize(sf::Vector2f(400, 200));
	rectangle.setFillColor(sf::Color::Red);

	if (!texture.loadFromFile(WALLPAPER_TEXTURE_FILE_PATH))
	{
		std::cout << "Unable to load " << WALLPAPER_TEXTURE_FILE_PATH << std::endl;
	}
	texture.setRepeated(true);
	wallpaper.setTexture(texture);
	wallpaper.setScale(sf::Vector2f(WALLPAPER_SCALE, WALLPAPER_SCALE));
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

	wallpaper.setTextureRect(sf::IntRect(0, 0, gameData->window->getSize().x, gameData->window->getSize().y + 32));
	float offset = -gameData->gameClock->getTime() * 20;
	offset = fmod(offset, 32 * WALLPAPER_SCALE);
	wallpaper.setPosition(sf::Vector2f(0, offset));
}


void MenuState::renderObjects()
{
	State::renderObjects();

	gameData->window->draw(wallpaper);
}
