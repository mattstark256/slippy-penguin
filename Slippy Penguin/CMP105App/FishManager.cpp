#include "FishManager.h"

#define FISH_TEXTURE_FILE_PATH "gfx/Fish.png"
#include <iostream>
#include "Framework/Collision.h"


FishManager::FishManager()
{
	if (!fishTexture.loadFromFile(FISH_TEXTURE_FILE_PATH))
	{
		std::cout << "Unable to load " << FISH_TEXTURE_FILE_PATH << std::endl;
	}
}


FishManager::~FishManager()
{
}


void FishManager::addFish(sf::Vector2i tile, int direction)
{
	GameObject* fish = new GameObject();
	fish->setSize(sf::Vector2f(16, 16));
	fish->setOrigin(fish->getSize() * 0.5f);
	fish->setCollisionBox(-3, -3, 6, 6);
	fish->setPosition((sf::Vector2f)(tile * 16 + sf::Vector2i(8, 8)));
	fish->setTexture(&fishTexture);
	fish->setTextureRect(sf::IntRect(direction * 16, 0, 16, 16));
	fishes.push_back(fish);
}


void FishManager::render(sf::RenderWindow * window)
{
	for (auto fish : fishes)
	{
		window->draw(*fish);
	}
}


bool FishManager::tryTakingFish(GameObject* playerObject)
{
	bool fishTaken = false;
	for (auto i = fishes.begin(); i != fishes.end();)
	{
		if (Collision::checkBoundingBox(playerObject, *i))
		{
			std::cout << "fish collected" << std::endl;
			i = fishes.erase(i);
			fishTaken = true;
		}
		else
		{
			i++;
		}
	}
	return fishTaken;
}
