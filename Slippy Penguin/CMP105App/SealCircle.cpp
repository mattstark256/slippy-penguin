#include "SealCircle.h"

#include <cmath>
#define TAU 6.28318530717958647692


SealCircle::SealCircle(sf::Vector2f _centre, float _radius, float _cyclePosition, float _cycleDuration, ParticleManager* _particleManager) :
	centre(_centre), radius(_radius), Seal(_cyclePosition, _cycleDuration, _particleManager)
{
}


SealCircle::~SealCircle()
{
}

void SealCircle::updatePosition()
{
	float radians = cyclePosition * TAU;
	sf::Vector2f radiusVector = sf::Vector2f(cos(radians), sin(radians)) * radius;
	setPosition(centre + radiusVector);

	directionVector = sf::Vector2f(-sin(radians), cos(radians));
}
