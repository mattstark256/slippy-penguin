#include "Seal.h"



Seal::Seal(float _cyclePosition, float _cycleDuration, ParticleManager* _particleManager) : cyclePosition(_cyclePosition), cycleDuration(_cycleDuration), particleManager(_particleManager)
{
	setSize(sf::Vector2f(32, 32));
	setOrigin(sf::Vector2f(16, 16));
	setTextureRect(sf::IntRect(0, 0, 32, 32));
	setCollisionBox(sf::FloatRect(-10, -7, 20, 14));
}


Seal::~Seal()
{
}


void Seal::update(float dt)
{
	switch (sealState)
	{
	case moving: move(dt); break;
	case eating: eat(dt); break;
	}
}


// Called by Penguin when they collide with a seal. Starts the eating animation.
void Seal::startEating()
{
	sealState = eating;
	eatTimer = 0;
}


// Called on update when sealState = moving
void Seal::move(float dt)
{
	cyclePosition += dt / cycleDuration;
	if (cyclePosition > 1) cyclePosition -= 1;
	updatePosition();

	// facingDirection is an int from 0 to 3 based on the direction of movement
	int facingDirection = abs(directionVector.x) < abs(directionVector.y) ? (directionVector.y > 0 ? 3 : 1) : (directionVector.x > 0 ? 0 : 2);
	// moveFrame alternates regularly between 0 and 1
	moveTimer += dt;
	int moveFrame = (int)(moveTimer / moveCycleDuration) % 2;
	// Pick a frame based on facingDirection and moveFrame
	setTextureRect(sf::IntRect(32 * moveFrame, 32 * facingDirection, 32, 32));

	// Emit ice particles at regular intervals
	moveParticleTimer += dt;
	if (moveParticleTimer > moveParticleinterval)
	{
		moveParticleTimer -= moveParticleinterval;
		sf::Vector2f trajectory = particleManager->getPointInEllipse(sf::Vector2f(0, -15), sf::Vector2f(50, 40));
		particleManager->createParticle(ice, getPosition(), trajectory, 50, 0.5, 1);
	}
}


// Called on update when sealState = eating
void Seal::eat(float dt)
{
	// Find the frame number based on how long they've been eating
	eatTimer += dt;
	int frame = (int)(eatTimer * 16);

	if (frame < EAT_FRAME_COUNT)
	{
		// Use the eatFrameTextures array too choose a texture
		setTextureRect(sf::IntRect(64, 32 * eatFrameTextures[frame], 32, 32));

		// Use the eatFrameBlood array to decide whether to emit blood particles
		if (eatFrameBlood[frame] == 1)
		{
			// Emit blood particles at regular intervals
			eatParticleTimer += dt;
			if (eatParticleTimer > eatParticleinterval)
			{
				eatParticleTimer -= eatParticleinterval;
				sf::Vector2f trajectory = particleManager->getPointInEllipse(sf::Vector2f(0, -30), sf::Vector2f(180, 50));
				particleManager->createParticle(blood, getPosition() + sf::Vector2f(0, -2), trajectory, 100, 0.3, 1);
			}
		}
	}
	else
	{
		// The animation has finished
		setTextureRect(sf::IntRect(64, 0, 32, 32));
	}
}


// This gets overridden by the derived seal classes
void Seal::updatePosition()
{
}
