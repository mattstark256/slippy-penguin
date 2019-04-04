#pragma once

#include <vector>
#include "Framework/GameObject.h"
#include "GameData.h"


// This keeps track of all the collectible fish, as well as keeping track of how many have been taken.
class FishManager
{
public:
	FishManager(GameData* _gameData);
	~FishManager();

	void addFish(sf::Vector2f position, int direction);
	void update(float dt);
	void render();
	void renderUI();
	bool tryTakingFish(GameObject* playerObject);
	bool allFishEaten();
	int getFishEaten();
	int getInitialFishCount();

private:
	GameData* gameData;
	std::vector<GameObject*> fishes;
	sf::Texture fishTexture;

	// The number of fish that have been generated
	int initialFishCount;

	sf::Text text;
	GameObject fishIcon;
	// When a fish is collected the fish counter UI temporarily expands, creating a pulse effect
	float textPulseAmount = 1;
};

