#include "Seal.h"



Seal::Seal(float _cyclePosition, float _cycleDuration) : cyclePosition(_cyclePosition), cycleDuration(_cycleDuration)
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
	cyclePosition += dt/cycleDuration;
	if (cyclePosition > 1) cyclePosition -= 1;
	updatePosition();
	int facingDirection = abs(directionVector.x) < abs(directionVector.y) ? (directionVector.y > 0 ? 3 : 1) : (directionVector.x > 0 ? 0 : 2);
	setTextureRect(sf::IntRect(0, 32 * facingDirection, 32, 32));
}

void Seal::updatePosition()
{
}
