#pragma once
#include "SFML\Graphics.hpp"


// This is the class used for emitted particles. I didn't inherit from GameObject because I wanted to keep particles as optimized as possible because there might be thousands on screen at once.
class Particle :
	public sf::RectangleShape
{
public:
	Particle(sf::Vector2f size, sf::Texture* texture);
	~Particle();

	void update(float dt);

	sf::Vector2f velocity;
	float fallSpeed = 0;

	float lifespan;
	float age = 0;
	bool alive = true; // This is used by ParticleMananger to get rid of dead particles

	int frames = 1; // How many frames the animation has
	float animationCycles = 1; // How many times the animation should be repeated in the particle's lifetime
};

