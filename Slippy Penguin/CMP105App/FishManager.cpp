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


// Adds a fish. Called when generating the level.
void FishManager::addFish(sf::Vector2f position, int direction)
{
	GameObject* fish = new GameObject();
	fish->setSize(sf::Vector2f(16, 16));
	fish->setOrigin(fish->getSize() * 0.5f);
	fish->setCollisionBox(-3, -3, 6, 6);
	fish->setPosition(position);
	fish->setTexture(&fishTexture);
	fish->setTextureRect(sf::IntRect(direction * 16, 0, 16, 16));
	fishes.push_back(fish);
	initialFishCount++;
}


void FishManager::update(float dt)
{
	// The fish counter UI lerps towards its default size
	textPulseAmount = textPulseAmount - (textPulseAmount - 1) * dt * 8;
}


void FishManager::render()
{
	for (auto fish : fishes)
	{
		gameData->window->draw(*fish);
	}
}


// Render the UI consisting of a fish icon and counter text.
void FishManager::renderUI()
{
	text.setString(std::to_string(initialFishCount - fishes.size()) + "/" + std::to_string(initialFishCount));
	text.setScale(sf::Vector2f(textPulseAmount, textPulseAmount));
	gameData->window->draw(fishIcon);
	gameData->window->draw(text);
}


// Check for any collisions and return true if the player has collided with a fish
bool FishManager::tryTakingFish(GameObject* playerObject)
{
	bool fishTaken = false;
	for (auto i = fishes.begin(); i != fishes.end();)
	{
		if (Collision::checkBoundingBox(playerObject, *i) && !fishTaken)
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
