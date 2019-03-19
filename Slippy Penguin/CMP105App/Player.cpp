#include "Player.h"

#include "Framework/Vector.h"
#define PLAYER_TEXTURE_FILE_PATH "gfx/Penguin.png"
#include <iostream>


Player::Player(GameData* _gameData, TilemapManager* _tilemap) : gameData(_gameData), tilemap(_tilemap)
{
	setSize(sf::Vector2f(16, 16));
	setCollider(true);
	setCollisionBox(6, 9, 4, 4);

	if (!texture.loadFromFile(PLAYER_TEXTURE_FILE_PATH))
	{
		std::cout << "Unable to load " << PLAYER_TEXTURE_FILE_PATH << std::endl;
	}
	setTexture(&texture);
	setTextureRect(sf::IntRect(0, 0, 16, 16));
}


Player::~Player()
{
}


void Player::handleInput(float dt)
{
	sf::Vector2f inputVector(0, 0);
	if (gameData->input->isKeyDown(sf::Keyboard::A)) { inputVector.x -= 1; }
	if (gameData->input->isKeyDown(sf::Keyboard::D)) { inputVector.x += 1; }
	if (gameData->input->isKeyDown(sf::Keyboard::W)) { inputVector.y -= 1; }
	if (gameData->input->isKeyDown(sf::Keyboard::S)) { inputVector.y += 1; }

	if (tilemap->checkForGround(this))
	{
		velocity = Vector::normalise(inputVector) * walkSpeed;
	}
	else if (tilemap->checkForIce(this))
	{
	}
	else
	{
		// Decelerate
		velocity = velocity * (1 - dt * 15);

		if (tilemap->checkForCliff(this))
		{
			// "Fall" downwards if the player is on a cliff. This avoids it looking like they lose without falling into the water.
			velocity += sf::Vector2f(0, dt * 500);
		}
		else
		{
			if (Vector::magnitude(velocity) < 10.0f)
			{
				// Die

				// This is a placeholder
				move(sf::Vector2f(0, 1000));
			}
		}
	}
	move(velocity * dt);


	// Decide which frame to use based on the walkTimer and movement direction.
	if (inputVector == sf::Vector2f(0, 0))
	{
		walkTimer = 0;
		walkPhase = 0;
	}
	else
	{
		walkTimer += dt;
		walkPhase = (int)(ceil(walkTimer * 4 / walkCycleDuration)) % 4;
		facingDirection = inputVector.x == 0 ? (inputVector.y > 0 ? 3 : 1) : (inputVector.x > 0 ? 0 : 2);
	}
	setTextureRect(sf::IntRect(walkPhase * 16, facingDirection * 16, 16, 16));
}


void Player::update(float dt)
{
}
