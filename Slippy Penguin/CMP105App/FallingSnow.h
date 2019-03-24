#pragma once
#include "Framework/GameObject.h"


class FallingSnow
{
public:
	FallingSnow();
	~FallingSnow();

	void update(float dt);
	void render(sf::RenderWindow* window);

private:
	float cycleTimer;
	float cycleDuration = 2;

	sf::Texture texture;

	GameObject snow1;
	GameObject snow2;
};

