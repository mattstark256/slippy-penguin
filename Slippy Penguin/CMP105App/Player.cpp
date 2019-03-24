#include "Player.h"

#include "Framework/Vector.h"
#include <iostream>
#include "LevelState.h"

#define PLAYER_TEXTURE_FILE_PATH "gfx/Penguin.png"


Player::Player(GameData* _gameData, LevelState* _level, TilemapManager* _tilemap, ParticleManager* _particleManager, FishManager* _fishManager, SealManager* _sealManager) :
	gameData(_gameData), level(_level), tilemap(_tilemap), particleManager(_particleManager), fishManager(_fishManager), sealManager(_sealManager)
{
	setSize(sf::Vector2f(16, 16));
	setOrigin(8, 11);
	setCollisionBox(-3, -2, 6, 4);

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
	switch (playerState)
	{
	case walking: walk(dt); break;
	case sliding: slide(dt); break;
	case falling: fall(dt); break;
	case whaleDeath: whaleDie(dt); break;
	case eating: eat(dt); break;
	case sealDeath: sealDie(dt); break;
	}
}


void Player::render()
{
	if (playerState != sealDeath)
	{
		gameData->window->draw(*this);
	}

	if (whaleSeamSplash != nullptr)
	{
		gameData->window->draw(*whaleSeamSplash);
	}
}


// Called on update when currentPlayerState is walking
void Player::walk(float dt)
{
	velocity = Vector::normalise(inputVector) * walkSpeed;
	move(velocity * dt);
	checkForCollisions();

	if (fishManager->allFishEaten())
	{
		level->win();
	}
	if (fishManager->tryTakingFish(this))
	{
		startEating();
	}

	if (sealManager->checkForSealAttack(this))
	{
		startSealDeath();
	}

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


// Called on update when currentPlayerState is sliding
void Player::slide(float dt)
{
	move(velocity * dt);
	checkForCollisions();

	fishManager->tryTakingFish(this);

	if (sealManager->checkForSealAttack(this))
	{
		startSealDeath();
	}

	setTextureRect(sf::IntRect(4 * 16, facingDirection * 16, 16, 16));

	slideParticleTimer += dt;
	if (slideParticleTimer > slideParticleinterval)
	{
		slideParticleTimer -= slideParticleinterval;
		sf::Vector2f trajectory = particleManager->getPointInEllipse(sf::Vector2f(0, -15), sf::Vector2f(50, 40));
		particleManager->createParticle(ice, getPosition(), trajectory, 50, 0.5, 1);
	}

}


// Called on update when currentPlayerState is falling
void Player::fall(float dt)
{
	fallTimer += dt;

	// Use f (float 0-1) to animate the player falling into the water
	float f = fallTimer / fallDuration;
	// horizontal (3D) position is a linear interpolation between the start and end positions
	sf::Vector2f horizontalPosition = (fallStartPos * (1 - f) + fallEndPos * f);
	// vertical (3D) position is a square of f, making the trajectory a parabola
	sf::Vector2f verticalPosition = sf::Vector2f(0, f * f * 5);
	setPosition(horizontalPosition + verticalPosition);
	if (f > 1)
	{
		startWhaleDeath();
	}

	setTextureRect(sf::IntRect(1 * 16, facingDirection * 16, 16, 16));
}


// Called on update when currentPlayerState is fallDeath
void Player::whaleDie(float dt)
{
	whaleTimer += dt;

	// Use f (float 0-1) to animate the player being grabbed by the whale
	float f = whaleTimer / whaleDuration;
	if (f < 1)
	{
		float sinkAmount = f * whaleSinkHeight;
		float jumpAmount = (1 - pow(f * 2 - 1, 2)) * whaleJumpHeight;
		setPosition(whaleStartPos + sf::Vector2f(0, sinkAmount + jumpAmount));
		int spriteHeight = 16 - sinkAmount - jumpAmount;
		setSize(sf::Vector2f(32, spriteHeight));

		int frame = fmod(whaleTimer * 16, 2);
		setTextureRect(sf::IntRect(frame * 32, 4 * 16, 32, spriteHeight));

		whaleParticleTimer += dt;
		if (whaleParticleTimer > whaleParticleinterval)
		{
			whaleParticleTimer -= whaleParticleinterval;
			sf::Vector2f trajectory = particleManager->getPointInEllipse(sf::Vector2f(0, -30), sf::Vector2f(120, 80));
			particleManager->createParticle(water, whaleStartPos, trajectory, 100, 0.5, 1);
		}

		frame = fmod(whaleTimer * 12, 2);
		whaleSeamSplash->setTextureRect(sf::IntRect(frame * 32, 7 * 16, 32, 16));
	}
	else
	{
		whaleSeamSplash = nullptr;
	}

	if (whaleTimer > whaleDuration + 1)
	{
		level->lose("You got devoured by a killer whale!");
	}
}


// Called on update when currentPlayerState is eating
void Player::eat(float dt)
{
	eatTimer += dt;
	if (eatTimer > eatDuration)
	{
		playerState = walking;
	}

	int frame = fmod(eatTimer * 12, 2);

	setTextureRect(sf::IntRect((5 + frame) * 16, facingDirection * 16, 16, 16));

	eatParticleTimer += dt;
	if (eatParticleTimer > eatParticleinterval)
	{
		eatParticleTimer -= eatParticleinterval;
		sf::Vector2f trajectory = particleManager->getPointInEllipse(sf::Vector2f(0, -20), sf::Vector2f(60, 30));
		particleManager->createParticle(food, getPosition() + sf::Vector2f(0, -7), trajectory, 50, 0.5, 1);
	}
}


void Player::sealDie(float dt)
{
	sealTimer += dt;
	if (sealTimer > sealDuration)
	{
		level->lose("You got chewed on by a seal!");
	}
}


// Check what the player is colliding with and react accordingly
void Player::checkForCollisions()
{
	sf::Vector2u currentTileCoords = (sf::Vector2u)tilemap->pointToTileCoords(getPosition());
	GameObject* currentTile = tilemap->getTile(currentTileCoords);
	if (currentTile)
	{
		if (currentTile->getCollisionTag() & 1)
		{
			playerState = walking;
		}
		else if (currentTile->getCollisionTag() & 2)
		{
			playerState = sliding;
		}
		else
		{
			startFalling();
		}
	}
}


// Prepare for falling PlayerState
void Player::startFalling()
{
	playerState = falling;
	fallTimer = 0;

	// Get the position where the fall starts
	fallStartPos = getPosition();

	// Get the position where the fall ends. The player should fall away from any nearby terrain.
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
		if (tileAbove && tileAbove->getCollisionTag() & 3 && fallEndPos.y < currentTileCentre.y - 1) { fallEndPos.y = currentTileCentre.y - 1; }
		if (tileBelow && tileBelow->getCollisionTag() & 3 && fallEndPos.y > currentTileCentre.y - 1) { fallEndPos.y = currentTileCentre.y - 1; }
		if (tileLeft && tileLeft->getCollisionTag() & 3 && fallEndPos.x < currentTileCentre.x - 0) { fallEndPos.x = currentTileCentre.x - 0; }
		if (tileRight && tileRight->getCollisionTag() & 3 && fallEndPos.x > currentTileCentre.x + 0) { fallEndPos.x = currentTileCentre.x + 0; }
	}
}


// Prepare for fallDeath PlayerState
void Player::startWhaleDeath()
{
	playerState = whaleDeath;
	whaleTimer = 0;
	whaleStartPos = getPosition();

	setSize(sf::Vector2f(32, 16));
	setOrigin(16, 16);
	setTextureRect(sf::IntRect(6 * 16, 0 * 16, 32, 16));

	whaleSeamSplash = new sf::RectangleShape();
	whaleSeamSplash->setSize(sf::Vector2f(32, 16));
	whaleSeamSplash->setOrigin(whaleSeamSplash->getSize()*0.5f);
	whaleSeamSplash->setPosition(whaleStartPos);
	whaleSeamSplash->setTexture(&texture);
	whaleSeamSplash->setTextureRect(sf::IntRect(0, 7 * 16, 32, 16));
}


// Prepare for eating PlayerState
void Player::startEating()
{
	playerState = eating;
	eatTimer = 0;
}


void Player::startSealDeath()
{
	playerState = sealDeath;
	sealTimer = 0;
}
