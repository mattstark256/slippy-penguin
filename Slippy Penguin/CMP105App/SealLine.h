#pragma once
#include "Seal.h"


// This type of seal moves back and forth along a line.
class SealLine :
	public Seal
{
public:
	SealLine(sf::Vector2f _point1, sf::Vector2f _point2, float _cyclePosition, float _cycleDuration, ParticleManager* _particleManager);
	~SealLine();

private:
	// The end points of the line
	sf::Vector2f point1;
	sf::Vector2f point2;

	void updatePosition();
};

