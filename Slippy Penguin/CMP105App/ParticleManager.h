#pragma once

#include <vector>
#include "Particle.h"

enum ParticleType { test, water, ice, blood, food };

class ParticleManager
{
public:
	ParticleManager();
	~ParticleManager();

	void update(float dt);
	void render(sf::RenderWindow* window);

	void createParticle(ParticleType particleType, sf::Vector2f position, sf::Vector2f velocity, float fallSpeed, float lifetime, float animationCycles);

	sf::Vector2f getPointInEllipse(sf::Vector2f offset, sf::Vector2f ellipseSize);

private:
	std::vector<Particle*> particles;

	sf::Texture testParticleTexture;
	sf::Texture waterParticleTexture;
	sf::Texture iceParticleTexture;
	sf::Texture bloodParticleTexture;
	sf::Texture foodParticleTexture;
};

