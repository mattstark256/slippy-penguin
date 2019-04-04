#pragma once

#include "Seal.h"
#include "GameData.h"
#include "Camera.h"
#include "ParticleManager.h"


// This class keeps track of all the seals in the level.
class SealManager
{
public:
	SealManager(GameData* _gameData, Camera* _camera, ParticleManager* _particleManager);
	~SealManager();

	void addSeal(sf::Vector2f centre, float radius, float cyclePosition, float cycleDuration);
	void addSeal(sf::Vector2f point1, sf::Vector2f point2, float cyclePosition, float cycleDuration);
	void update(float dt);
	void render();
	bool checkForSealAttack(GameObject* playerObject);

private:
	GameData* gameData;
	Camera* camera;
	ParticleManager* particleManager;
	std::vector<Seal*> seals;
	sf::Texture sealTexture;
};

