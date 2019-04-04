#pragma once
#include "Seal.h"


// This type of seal moves around a circular route.
class SealCircle :
	public Seal
{
public:
	SealCircle(sf::Vector2f _centre, float _radius, float _cyclePosition, float _cycleDuration, ParticleManager* _particleManager);
	~SealCircle();

private:
	// The parameters of the route
	sf::Vector2f centre;
	float radius;

	void updatePosition();
};

