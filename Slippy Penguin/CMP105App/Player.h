#pragma once
#include "Framework/GameObject.h"

#include "GameData.h"
#include "TilemapManager.h"
#include "ParticleManager.h"


enum PlayerState { walking, sliding, falling, fallDeath };


class Player :
	public GameObject
{
public:
	Player(GameData* _gameData, TilemapManager* _tilemap, ParticleManager* _particleManager);
	~Player();

	void handleInput(float dt);
	void update(float dt);
	void render();

private:
	GameData* gameData;
	TilemapManager* tilemap;
	ParticleManager* particleManager;
	sf::Texture texture;

	PlayerState currentPlayerState;

	// Variables for the walking PlayerState
	float walkSpeed = 60;
	sf::Vector2f inputVector;
	float walkTimer;
	int walkPhase;
	int facingDirection;
	float walkCycleDuration = 0.3f;

	// Variables for the sliding PlayerState
	float slideParticleTimer;
	float slideParticleinterval = 0.05f;

	// Variables for the falling PlayerState
	sf::Vector2f fallStartPos;
	sf::Vector2f fallEndPos;
	float fallTimer;
	float fallDuration = 0.3f;

	// Variables for the fallDeath PlayerState
	sf::Vector2f dieStartPos;
	float dieTimer;
	float dieDuration = 1.8f;
	float dieSinkHeight = 16;
	float dieJumpHeight = -32;
	float dieParticleTimer;
	float dieParticleinterval = 0.01f;
	sf::RectangleShape* seamSplash; // This is a sprite used to cover the seam at the bottom of the killer whale


	void walk(float dt);
	void slide(float dt);
	void fall(float dt);
	void fallDie(float dt);
	void checkForCollisions();
	void startFalling();
	void startFallDeath();
};

