#pragma once
#include "Seal.h"


class SealLine :
	public Seal
{
public:
	SealLine(sf::Vector2f _point1, sf::Vector2f _point2, float _cyclePosition, float _cycleDuration, ParticleManager* _particleManager);
	~SealLine();

private:
	sf::Vector2f point1;
	sf::Vector2f point2;

	void updatePosition();
};

