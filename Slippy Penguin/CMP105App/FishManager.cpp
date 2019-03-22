#include "FishManager.h"

#define FISH_TEXTURE_FILE_PATH "gfx/Fish.png"
#include <iostream>
#include "Framework/Collision.h"


FishManager::FishManager(GameData* _gameData) : gameData(_gameData)
{
	if (!fishTexture.loadFromFile(FISH_TEXTURE_FILE_PATH))
	{
		std::cout << "Unable to load " << FISH_TEXTURE_FILE_PATH << std::endl;
	}

	text.setString("Test");
	gameData->fontSettings->applyTitleSettings(&text);
	text.setOrigin(40, 30);
	text.setPosition(sf::Vector2f(140, 60));

	fishIcon.setTexture(&fishTexture);
	fishIcon.setSize(sf::Vector2f(100, 100));
	fishIcon.setTextureRect(sf::IntRect(0, 0, 16, 16));
	fishIcon.setPosition(sf::Vector2f(10, 10));
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
	initialFishCount++;
}


void FishManager::update(float dt)
{
	textPulseAmount = textPulseAmount - (textPulseAmount - 1) * dt * 8;
}


void FishManager::render()
{
	for (auto fish : fishes)
	{
		gameData->window->draw(*fish);
	}
}


void FishManager::renderUI()
{
	text.setString(std::to_string(initialFishCount - fishes.size()) + "/" + std::to_string(initialFishCount));
	text.setScale(sf::Vector2f(textPulseAmount, textPulseAmount));
	gameData->window->draw(fishIcon);
	gameData->window->draw(text);
}


bool FishManager::tryTakingFish(GameObject* playerObject)
{
	bool fishTaken = false;
	for (auto i = fishes.begin(); i != fishes.end();)
	{
		if (Collision::checkBoundingBox(playerObject, *i))
		{
			i = fishes.erase(i);
			fishTaken = true;
			textPulseAmount = 1.5f;
		}
		else
		{
			i++;
		}
	}
	return fishTaken;
}


bool FishManager::allFishEaten()
{
	return (fishes.size() == 0);
}


int FishManager::getFishEaten()
{
	return initialFishCount - fishes.size();
}


int FishManager::getInitialFishCount()
{
	return initialFishCount;
}
