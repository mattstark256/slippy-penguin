#pragma once
#include "SFML\Graphics.hpp"


class Particle :
	public sf::RectangleShape
{
public:
	Particle(sf::Vector2f size, sf::Texture* texture);
	~Particle();

	virtual void update(float dt);

	sf::Vector2f velocity;
	float fallSpeed = 0;

	float lifespan;
	float age = 0;
	bool alive = true;

	int frames = 1;
	float animationCycles = 1;
};

