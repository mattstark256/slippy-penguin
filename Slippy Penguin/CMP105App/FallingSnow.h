#pragma once
#include "Framework/GameObject.h"


// This is the falling snow effect which appears in the foreground of every level.
class FallingSnow
{
public:
	FallingSnow();
	~FallingSnow();

	void update(float dt);
	void render(sf::RenderWindow* window);

private:
	float cycleTimer;

	sf::Texture texture;

	GameObject snow1;
	GameObject snow2;
};

