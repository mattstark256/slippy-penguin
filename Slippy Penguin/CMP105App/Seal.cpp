#include "Seal.h"



Seal::Seal(float _cyclePosition, float _cycleDuration, ParticleManager* _particleManager) : cyclePosition(_cyclePosition), cycleDuration(_cycleDuration), particleManager(_particleManager)
{
	setSize(sf::Vector2f(32, 32));
	setOrigin(sf::Vector2f(16, 16));
	setTextureRect(sf::IntRect(0, 0, 32, 32));
	setCollisionBox(sf::FloatRect(-7, -5, 14, 10));
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


void Seal::startEating()
{
	sealState = eating;
	eatTimer = 0;
}


void Seal::move(float dt)
{
	cyclePosition += dt / cycleDuration;
	if (cyclePosition > 1) cyclePosition -= 1;
	updatePosition();
	int facingDirection = abs(directionVector.x) < abs(directionVector.y) ? (directionVector.y > 0 ? 3 : 1) : (directionVector.x > 0 ? 0 : 2);

	moveTimer += dt;
	int moveFrame = (int)(moveTimer / moveCycleDuration) % 2;


	setTextureRect(sf::IntRect(32 * moveFrame, 32 * facingDirection, 32, 32));


	moveParticleTimer += dt;
	if (moveParticleTimer > moveParticleinterval)
	{
		moveParticleTimer -= moveParticleinterval;
		sf::Vector2f trajectory = particleManager->getPointInEllipse(sf::Vector2f(0, -15), sf::Vector2f(50, 40));
		particleManager->createParticle(ice, getPosition(), trajectory, 50, 0.5, 1);
	}
}


void Seal::eat(float dt)
{
	eatTimer += dt;

	int frame = (int)(eatTimer * 16);

	if (frame < EAT_FRAME_COUNT)
	{
		setTextureRect(sf::IntRect(64, 32 * eatFrameTextures[frame], 32, 32));

		if (eatFrameBlood[frame] == 1)
		{
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
		setTextureRect(sf::IntRect(64, 0, 32, 32));
	}
}


void Seal::updatePosition()
{
}
