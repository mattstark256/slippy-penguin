#include "ParticleManager.h"

#include <iostream>
#include <stdlib.h> // rand
#include "Framework/Vector.h"
#define TEST_PARTICLE_FILE_PATH "gfx/Particles/TestParticle.png"
#define WATER_PARTICLE_FILE_PATH "gfx/Particles/WaterParticle.png"
#define ICE_PARTICLE_FILE_PATH "gfx/Particles/IceParticle.png"
#define BLOOD_PARTICLE_FILE_PATH "gfx/Particles/BloodParticle2.png"
#define FOOD_PARTICLE_FILE_PATH "gfx/Particles/FoodParticle.png"


ParticleManager::ParticleManager()
{
	if (!testParticleTexture.loadFromFile(TEST_PARTICLE_FILE_PATH))
	{
		std::cout << "Unable to load " << TEST_PARTICLE_FILE_PATH << std::endl;
	}
	if (!iceParticleTexture.loadFromFile(ICE_PARTICLE_FILE_PATH))
	{
		std::cout << "Unable to load " << ICE_PARTICLE_FILE_PATH << std::endl;
	}
	if (!waterParticleTexture.loadFromFile(WATER_PARTICLE_FILE_PATH))
	{
		std::cout << "Unable to load " << WATER_PARTICLE_FILE_PATH << std::endl;
	}
	if (!bloodParticleTexture.loadFromFile(BLOOD_PARTICLE_FILE_PATH))
	{
		std::cout << "Unable to load " << BLOOD_PARTICLE_FILE_PATH << std::endl;
	}
	if (!foodParticleTexture.loadFromFile(FOOD_PARTICLE_FILE_PATH))
	{
		std::cout << "Unable to load " << FOOD_PARTICLE_FILE_PATH << std::endl;
	}
}


ParticleManager::~ParticleManager()
{
}


// Update all particles and destroy any dead ones
void ParticleManager::update(float dt)
{
	for (auto i = particles.begin(); i != particles.end();)
	{
		if (!(*i)->alive)
		{
			(*i)->~Particle();
			i = particles.erase(i);
		}
		else
		{
			(*i)->update(dt);
			i++;
		}
	}
}


void ParticleManager::render(sf::RenderWindow* window)
{
	for (Particle* particle : particles)
	{
		if (particle->alive)
		{
			window->draw(*particle);
		}
	}
}


void ParticleManager::createParticle(ParticleType particleType, sf::Vector2f position, sf::Vector2f velocity, float fallSpeed, float lifespan, float animationCycles)
{
	Particle* particle = nullptr;

	switch (particleType)
	{
	case test:
		particle = new Particle(sf::Vector2f(8, 8), &testParticleTexture);
		particle->frames = 4;
		break;
	case water:
		particle = new Particle(sf::Vector2f(8, 8), &waterParticleTexture);
		particle->frames = 4;
		break;
	case ice:
		particle = new Particle(sf::Vector2f(1, 1), &iceParticleTexture);
		break;
	case blood:
		particle = new Particle(sf::Vector2f(1, 1), &bloodParticleTexture);
		break;
	case food:
		particle = new Particle(sf::Vector2f(1, 1), &foodParticleTexture);
		break;
	}

	if (particle != nullptr)
	{
		particle->setPosition(position);
		particle->velocity = velocity;
		particle->fallSpeed = fallSpeed;
		particle->lifespan = lifespan;
		particle->animationCycles = animationCycles;
		particles.push_back(particle);
	}
}


// Get a random point in an ellipse with centre ellipseCentre and dimensions ellipseSize. This is useful for generating particle trajectories.
sf::Vector2f ParticleManager::getPointInEllipse(sf::Vector2f ellipseCentre, sf::Vector2f ellipseSize)
{
	// Find a random point in a circle with diameter 1
	sf::Vector2f point;
	bool trajectoryFound = false;
	while (!trajectoryFound)
	{
		point = sf::Vector2f((double)rand() / RAND_MAX - 0.5f, (double)rand() / RAND_MAX - 0.5f);
		if (Vector::magnitude(point) < 0.5f)
		{
			trajectoryFound = true;
		}
	}

	return ellipseCentre + sf::Vector2f(point.x * ellipseSize.x, point.y * ellipseSize.y);
}
