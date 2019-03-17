#pragma once

#include "GameData.h"


class Camera
{
public:
	Camera(GameData* _gameData);
	~Camera();

	void setPosition(sf::Vector3f _position);
	void move(sf::Vector3f _moveVector);
	void setVerticalFov(float _verticalFov);

	sf::View getCameraView();

private:
	GameData* gameData;

	// 3D position of camera, with positive z being away from the screen
	sf::Vector3f position = sf::Vector3f(0, 0, 500);

	// vertical field of view in degrees
	float verticalFov = 60;
};

