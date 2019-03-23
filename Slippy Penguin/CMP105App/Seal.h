#pragma once
#include "Framework/GameObject.h"

class Seal :
	public GameObject
{
public:
	Seal(float _cyclePosition, float _cycleDuration);
	~Seal();

	void update(float dt);

protected:
	float cyclePosition; // 0-1
	float cycleDuration;
	sf::Vector2f directionVector;

	virtual void updatePosition();
};

