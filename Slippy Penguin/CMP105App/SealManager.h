#pragma once

#include "Seal.h"
#include "GameData.h"


class SealManager
{
public:
	SealManager(GameData* _gameData);
	~SealManager();

	void addSeal(sf::Vector2f centre, float radius, float cyclePosition, float cycleDuration);
	void addSeal(sf::Vector2f point1, sf::Vector2f point2, float cyclePosition, float cycleDuration);
	void update(float dt);
	void render();
	Seal* checkForCollision(GameObject* playerObject);

private:
	GameData* gameData;
	std::vector<Seal*> seals;
	sf::Texture sealTexture;
};

