#include "FallingSnow.h"

#include <iostream>

#define SNOW_TEXTURE_FILE_PATH "gfx/Snow.png"


FallingSnow::FallingSnow()
{
	if (!texture.loadFromFile(SNOW_TEXTURE_FILE_PATH))
	{
		std::cout << "Unable to load " << SNOW_TEXTURE_FILE_PATH << std::endl;
	}

	snow1.setSize(sf::Vector2f(3000, 3000));
	snow2.setSize(sf::Vector2f(3000, 3000));
	snow1.setTextureRect(sf::IntRect(0, 0, 3000, 3000));
	snow2.setTextureRect(sf::IntRect(0, 0, 3000, 3000));
	texture.setRepeated(true);
	snow1.setTexture(&texture);
	snow2.setTexture(&texture);
	snow2.setScale(-1, 1);
	snow2.setOrigin(3000, 0);
	
}


FallingSnow::~FallingSnow()
{
}


void FallingSnow::update(float dt)
{
	cycleTimer += dt / cycleDuration;

	snow1.setPosition(fmod(cycleTimer * 16, 128) - 1000, fmod(cycleTimer * 32, 128) - 1000);
	snow2.setPosition(fmod(cycleTimer * 8, 128) - 1000, fmod(cycleTimer * 16, 128) - 1000);
}

void FallingSnow::render(sf::RenderWindow * window)
{
	window->draw(snow1);
	window->draw(snow2);
}
