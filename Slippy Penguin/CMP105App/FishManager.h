#pragma once

#include <vector>
#include "Framework/GameObject.h"
#include "GameData.h"


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
	int initialFishCount;

	sf::Text text;
	GameObject fishIcon;
	float textPulseAmount = 1;
};

