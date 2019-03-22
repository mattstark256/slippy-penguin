#pragma once

#include <vector>
#include "Framework/GameObject.h"


class FishManager
{
public:
	FishManager();
	~FishManager();

	void addFish(sf::Vector2i tile, int direction);
	void render(sf::RenderWindow* window);
	bool tryTakingFish(GameObject* playerObject);

private:
	std::vector<GameObject*> fishes;
	sf::Texture fishTexture;
};

