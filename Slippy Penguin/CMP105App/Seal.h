#pragma once
#include "Framework/GameObject.h"

#include "ParticleManager.h"
#define EAT_FRAME_COUNT 26


// This is the base class for seals. The derived classes are for the different movement patterns.
class Seal :
	public GameObject
{
public:
	Seal(float _cyclePosition, float _cycleDuration, ParticleManager* _particleManager);
	~Seal();

	void update(float dt);
	void startEating();

protected:
	ParticleManager* particleManager;

	// SealState is the current behaviour of the seal
	enum SealState { moving, eating };
	SealState sealState = moving;

	// CyclePosition loops through the range 0-1 every cycleDuration seconds. CyclePosition is used by the derived seal classes to get a position based on their movement pattern.
	float cyclePosition;
	float cycleDuration;
	// DirectionVector is set by the derived classes and is used for choosing which animation frame should be used.
	sf::Vector2f directionVector;

	// Variables for the movement animation
	float moveTimer;
	float moveCycleDuration = 0.2f;
	// Variables for emitting particles as they move
	float moveParticleTimer;
	float moveParticleinterval = 0.09f;

	// Variables for the eating animation
	float eatTimer = 0;
	// The sequence of frames for the eating animation
	int eatFrameTextures[EAT_FRAME_COUNT] = { 0, 1, 0, 2, 0, 1, 0, 2, 0, 1, 0, 2, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2, 0, 1, 0, 2 };
	// Which of the above frames should have blood particles emitted
	int eatFrameBlood[EAT_FRAME_COUNT] =    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0 };
	// Variables for emitting blood particles as they eat
	float eatParticleTimer;
	float eatParticleinterval = 0.02f;

	void move(float dt);
	void eat(float dt);

	// This is overridden by the derived classes and is used for movement patterns.
	virtual void updatePosition();
};

