#pragma once
#include "Framework/GameObject.h"

#include "GameData.h"
class LevelState; // This is needed in order to avoid circular dependency
#include "TilemapManager.h"
#include "ParticleManager.h"
#include "FishManager.h"
#include "SealManager.h"


class Player :
	public GameObject
{
public:
	Player(GameData* _gameData, LevelState* _level, TilemapManager* _tilemap, ParticleManager* _particleManager, FishManager* _fishManager, SealManager* _sealManager);
	~Player();

	void handleInput(float dt);
	void update(float dt);
	void render();

	void setFacingDirection(int _facingDirection) { facingDirection = _facingDirection; }

private:
	enum PlayerState { walking, sliding, falling, whaleDeath, eating, sealDeath };

	GameData* gameData;
	LevelState* level;
	TilemapManager* tilemap;
	ParticleManager* particleManager;
	FishManager* fishManager;
	SealManager* sealManager;


	sf::Texture texture;

	PlayerState playerState;

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

	// Variables for the whaleDeath PlayerState
	sf::Vector2f whaleStartPos;
	float whaleTimer;
	float whaleDuration = 1.8f;
	float whaleSinkHeight = 16;
	float whaleJumpHeight = -32;
	float whaleParticleTimer;
	float whaleParticleinterval = 0.01f;
	sf::RectangleShape* whaleSeamSplash; // This is a sprite used to cover the seam at the bottom of the killer whale

	// Variables for the eating PlayerState
	float eatTimer;
	float eatDuration = 0.5f;
	float eatParticleTimer;
	float eatParticleinterval = 0.06f;

	// Variables for the sealDeath PlayerState
	float sealTimer;
	float sealDuration = 2.7f;


	void walk(float dt);
	void slide(float dt);
	void fall(float dt);
	void whaleDie(float dt);
	void eat(float dt);
	void sealDie(float dt);
	void checkForCollisions();
	void startFalling();
	void startWhaleDeath();
	void startEating();
	void startSealDeath();
};

