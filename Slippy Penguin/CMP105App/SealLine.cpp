#include "SealLine.h"



SealLine::SealLine(sf::Vector2f _point1, sf::Vector2f _point2, float _cyclePosition, float _cycleDuration, ParticleManager* _particleManager) :
	point1(_point1), point2(_point2), Seal(_cyclePosition, _cycleDuration, _particleManager)
{
}


SealLine::~SealLine()
{
}

void SealLine::updatePosition()
{
	float f = cyclePosition * 2;
	if (f > 1) f = 2 - f;
	setPosition(point1 * (1 - f) + point2 * f);

	directionVector = cyclePosition > 0.5f ? point1 - point2 : point2 - point1;
}
