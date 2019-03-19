#pragma once
#include "Framework/GameObject.h"

#include "GameData.h"
#include "TilemapManager.h"


class Player :
	public GameObject
{
public:
	Player(GameData* _gameData, TilemapManager* _tilemap);
	~Player();

	void handleInput(float dt);
	void update(float dt);

private:
	GameData* gameData;
	TilemapManager* tilemap;
	float walkSpeed = 60;
	sf::Texture texture;

	sf::Vector2f inputVector;

	float walkTimer;
	int walkPhase;
	int facingDirection;
	float walkCycleDuration = 0.3f;

	bool isFalling;
	sf::Vector2f fallStartPos;
	sf::Vector2f fallEndPos;
	float fallTimer;
	float fallDuration = 0.2f;

	void walk(float dt);
	void slide(float dt);
	void fall(float dt);
	void startFalling();
};

