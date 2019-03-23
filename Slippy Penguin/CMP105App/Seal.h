#pragma once
#include "Framework/GameObject.h"

#include "ParticleManager.h"
#define EAT_FRAME_COUNT 26


class Seal :
	public GameObject
{
public:
	Seal(float _cyclePosition, float _cycleDuration, ParticleManager* _particleManager);
	~Seal();

	void update(float dt);
	void startEating();

protected:
	enum SealState { moving, eating };
	ParticleManager* particleManager;

	float cyclePosition; // 0-1
	float cycleDuration;
	sf::Vector2f directionVector;
	SealState sealState = moving;

	float moveTimer;
	float moveCycleDuration = 0.2f;
	float moveParticleTimer;
	float moveParticleinterval = 0.09f;

	float eatTimer = 0;
	int eatFrameTextures[EAT_FRAME_COUNT] = { 0, 1, 0, 2, 0, 1, 0, 2, 0, 1, 0, 2, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2, 0, 1, 0, 2 };
	int eatFrameBlood[EAT_FRAME_COUNT] =    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0 };
	float eatParticleTimer;
	float eatParticleinterval = 0.02f;

	void move(float dt);
	void eat(float dt);
	virtual void updatePosition();
};

