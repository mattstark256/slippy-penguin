#include "Camera.h"

#define DEGREES_TO_RADIANS 0.0174533


Camera::Camera(GameData* _gameData) : gameData(_gameData)
{
}


Camera::~Camera()
{
}


void Camera::setPosition(sf::Vector3f _position)
{
	position = _position;
}


void Camera::move(sf::Vector3f _moveVector)
{
	position += _moveVector;
}


void Camera::setVerticalFov(float _verticalFov)
{
	verticalFov = _verticalFov;
}


sf::View Camera::getCameraView()
{
	float aspectRatio = (float)gameData->window->getSize().x / gameData->window->getSize().y;
	float viewAreaHeight = position.z * tan(verticalFov * DEGREES_TO_RADIANS / 2) * 2;
	return sf::View(sf::Vector2f(position.x, position.y), sf::Vector2f(viewAreaHeight * aspectRatio, viewAreaHeight));
}
