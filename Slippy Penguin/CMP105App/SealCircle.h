#pragma once
#include "Seal.h"


class SealCircle :
	public Seal
{
public:
	SealCircle(sf::Vector2f _centre, float _radius, float _cyclePosition, float _cycleDuration, ParticleManager* _particleManager);
	~SealCircle();

private:
	sf::Vector2f centre;
	float radius;

	void updatePosition();
};

