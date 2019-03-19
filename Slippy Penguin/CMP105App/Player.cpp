#include "Player.h"

#include "Framework/Vector.h"
#define PLAYER_TEXTURE_FILE_PATH "gfx/Penguin.png"
#include <iostream>


Player::Player(GameData* _gameData, TilemapManager* _tilemap) : gameData(_gameData), tilemap(_tilemap)
{
	setSize(sf::Vector2f(16, 16));
	setCollisionBox(-2, -2, 4, 4);
	setOrigin(8, 11);

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

	inputVector = sf::Vector2f(0, 0);
	if (gameData->input->isKeyDown(sf::Keyboard::A)) { inputVector.x -= 1; }
	if (gameData->input->isKeyDown(sf::Keyboard::D)) { inputVector.x += 1; }
	if (gameData->input->isKeyDown(sf::Keyboard::W)) { inputVector.y -= 1; } 
	if (gameData->input->isKeyDown(sf::Keyboard::S)) { inputVector.y += 1; }

	

}


void Player::update(float dt)
{
	if (!isFalling)
	{
		sf::Vector2u currentTileCoords = (sf::Vector2u)tilemap->pointToTileCoords(getPosition());
		GameObject* currentTile = tilemap->getTile(currentTileCoords);
		if (currentTile)
		{
			if (currentTile->getCollisionTag() & 1)
			{
				walk(dt);
			}
			else if (currentTile->getCollisionTag() & 2)
			{
				slide(dt);
			}
			else
			{
				startFalling();
			}
		}
	}

	if (isFalling)
	{
		fall(dt);
	}

	move(velocity * dt);
}


void Player::walk(float dt)
{
	velocity = Vector::normalise(inputVector) * walkSpeed;

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


void Player::slide(float dt)
{
	setTextureRect(sf::IntRect(4 * 16, facingDirection * 16, 16, 16));
}


void Player::fall(float dt)
{
	// falling doesn't GameObject velocity, instead it uses setPosition()
	velocity = sf::Vector2f(0, 0);

	fallTimer += dt;

	// Use f (float 0-1) to animate the player falling into the water
	float f = fallTimer/fallDuration;
	if (f < 1)
	{
		// horizontal (3D) position is a linear interpolation between the start and end positions
		sf::Vector2f horizontalPosition = (fallStartPos * (1 - f) + fallEndPos * f);
		// vertical (3D) position is a square of f, making the trajectory a parabola
		sf::Vector2f verticalPosition = sf::Vector2f(0, f * f * 5); 
		setPosition(horizontalPosition + verticalPosition);
	}
}


void Player::startFalling()
{
	isFalling = true;
	fallTimer = 0;

	fallStartPos = getPosition();

	// The player should fall to a point where they are fully overlapping water.
	fallEndPos = getPosition();
	sf::Vector2u currentTileCoords = (sf::Vector2u)tilemap->pointToTileCoords(getPosition());
	GameObject* currentTile = tilemap->getTile(currentTileCoords);
	if (currentTile)
	{
		sf::Vector2f currentTileCentre = currentTile->getPosition() + currentTile->getSize() * 0.5f;
		GameObject* tileAbove = tilemap->getTile(sf::Vector2u(currentTileCoords.x, currentTileCoords.y - 1));
		GameObject* tileBelow = tilemap->getTile(sf::Vector2u(currentTileCoords.x, currentTileCoords.y + 1));
		GameObject* tileLeft = tilemap->getTile(sf::Vector2u(currentTileCoords.x - 1, currentTileCoords.y));
		GameObject* tileRight = tilemap->getTile(sf::Vector2u(currentTileCoords.x + 1, currentTileCoords.y));
		if (tileAbove && tileAbove->getCollisionTag() & 3 && fallEndPos.y < currentTileCentre.y - 0) { fallEndPos.y = currentTileCentre.y - 0; }
		if (tileBelow && tileBelow->getCollisionTag() & 3 && fallEndPos.y > currentTileCentre.y + 0) { fallEndPos.y = currentTileCentre.y + 0; }
		if (tileLeft && tileLeft->getCollisionTag() & 3 && fallEndPos.x < currentTileCentre.x - 1) { fallEndPos.x = currentTileCentre.x - 1; }
		if (tileRight && tileRight->getCollisionTag() & 3 && fallEndPos.x > currentTileCentre.x + 1) { fallEndPos.x = currentTileCentre.x + 1; }
		//fallEndPos += sf::Vector2f(0, 5);
	}
}
