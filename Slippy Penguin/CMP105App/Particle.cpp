#include "Particle.h"



Particle::Particle(sf::Vector2f size, sf::Texture* texture)
{
	setSize(size);
	setOrigin(size*0.5f);
	// The size is used both for the object size and the texture rect. All the in-game textures use 1 unit world space = 1 pixel to ensure a uniform level of pixellation.
	setTextureRect(sf::IntRect(sf::Vector2i(0, 0), (sf::Vector2i)size));
	setTexture(texture);
}


Particle::~Particle()
{
}


void Particle::update(float dt)
{
	move(velocity * dt);
	velocity += sf::Vector2f(0, fallSpeed) * dt;

	age += dt;
	if (age > lifespan)
	{
		alive = false;
	}

	int frame = ((int)((age / lifespan) * animationCycles * frames)) % frames;
	setTextureRect(sf::IntRect(sf::Vector2i(frame * getSize().x, 0), (sf::Vector2i)getSize()));
}
