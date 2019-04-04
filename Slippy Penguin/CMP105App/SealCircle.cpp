#include "SealCircle.h"

#include <cmath>
#define TAU 6.283185307


SealCircle::SealCircle(sf::Vector2f _centre, float _radius, float _cyclePosition, float _cycleDuration, ParticleManager* _particleManager) :
	centre(_centre), radius(_radius), Seal(_cyclePosition, _cycleDuration, _particleManager)
{
}


SealCircle::~SealCircle()
{
}


// Sets the position to a point on a circle based on cyclePosition. This is called on update by the parent class.
void SealCircle::updatePosition()
{
	float radians = cyclePosition * TAU;
	sf::Vector2f radiusVector = sf::Vector2f(cos(radians), sin(radians)) * radius;
	setPosition(centre + radiusVector);

	// Get a vector representing the direction of movement. It's multiplied by cycleDuration so that seals moving in reverse have a reversed directionVector.
	directionVector = sf::Vector2f(-sin(radians), cos(radians)) * cycleDuration;
}
