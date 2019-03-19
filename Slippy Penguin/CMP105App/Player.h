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

	float walkTimer;
	int walkPhase;
	int facingDirection;
	float walkCycleDuration = 0.3f;
};

