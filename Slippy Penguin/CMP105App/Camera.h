#pragma once

#include "GameData.h"
#include "Framework/GameObject.h"


class Camera
{
public:
	Camera(GameData* _gameData);
	~Camera();

	void setPosition(sf::Vector3f _position);
	void move(sf::Vector3f _moveVector);
	void setVerticalFov(float _verticalFov);
	void update(float dt);
	void setSubject(GameObject* _subject) { subject = _subject; }
	void jumpToTarget();

	sf::View getCameraView();


private:
	GameData* gameData;

	// 3D position of camera, with positive z being away from the screen
	sf::Vector3f position = sf::Vector3f(0, 0, 300);
	sf::Vector3f targetPosition = sf::Vector3f(0, 0, 150);

	// vertical field of view in degrees
	float verticalFov = 60;

	// If a subject is specified it will lerp towards its position
	GameObject* subject;
	float followSpeed = 7;
	sf::Vector3f followOffset = sf::Vector3f(0, 0, 150);

	void updateTargetPosition();
};

