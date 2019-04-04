#pragma once

#include "GameData.h"
#include "Framework/GameObject.h"


// This is the camera viewing a level. It has a 3-dimensional position so it can zoom in and out.
class Camera
{
public:
	Camera(GameData* _gameData);
	~Camera();

	void update(float dt);
	void setSubject(GameObject* _subject) { subject = _subject; }
	void jumpToTarget();

	sf::View getCameraView();


private:
	GameData* gameData;

	// vertical field of view in degrees
	float verticalFov = 60;

	// 3D position of camera, with positive z being away from the screen
	sf::Vector3f position = sf::Vector3f(0, 0, 300);

	// The position the camera is moving towards
	sf::Vector3f targetPosition = sf::Vector3f(0, 0, 150);

	// If a subject is specified the camera will move towards its position plus followOffset
	GameObject* subject;
	sf::Vector3f followOffset = sf::Vector3f(0.01, 0.01, 150); // The 0.01s prevent floating point errors when the camera lines up exactly with the pixel grid.

	float moveSpeed = 7;

	void updateTargetPosition();
};

