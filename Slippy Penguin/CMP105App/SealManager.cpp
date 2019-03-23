#include "SealManager.h"

#include "SealCircle.h"
#include "SealLine.h"
#include <iostream>
#include "Framework/Collision.h"

#define SEAL_TEXTURE_FILE_PATH "gfx/Seal.png"


SealManager::SealManager(GameData* _gameData) : gameData(_gameData)
{
	if (!sealTexture.loadFromFile(SEAL_TEXTURE_FILE_PATH))
	{
		std::cout << "Unable to load " << SEAL_TEXTURE_FILE_PATH << std::endl;
	}
}


SealManager::~SealManager()
{
}


void SealManager::addSeal(sf::Vector2f centre, float radius, float cyclePosition, float cycleDuration)
{
	SealCircle* seal = new SealCircle(centre, radius, cyclePosition, cycleDuration);
	seal->setTexture(&sealTexture);
	seals.push_back(seal);
}


void SealManager::addSeal(sf::Vector2f point1, sf::Vector2f point2, float cyclePosition, float cycleDuration)
{
	SealLine* seal = new SealLine(point1, point2, cyclePosition, cycleDuration);
	seal->setTexture(&sealTexture);
	seals.push_back(seal);
}


void SealManager::update(float dt)
{
	for (auto seal : seals)
	{
		seal->update(dt);
	}
}


void SealManager::render()
{
	for (auto seal : seals)
	{
		gameData->window->draw(*seal);
	}
}


bool SealManager::checkForSealAttack(GameObject* playerObject)
{
	bool attacked = false;
	for (auto i = seals.begin(); i != seals.end();)
	{
		if (Collision::checkBoundingBox(playerObject, *i) && !attacked)
		{
			attacked = true;
		}
		else
		{
			i++;
		}
	}
	return attacked;
}
