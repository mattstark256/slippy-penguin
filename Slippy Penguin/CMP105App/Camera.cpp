#include "Camera.h"
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


void Camera::update(float dt)
{
	updateTargetPosition();

	float lerpValue = dt * followSpeed;
	position = position * (1 - lerpValue) + targetPosition * lerpValue;
}


void Camera::jumpToTarget()
{
	updateTargetPosition();
	position = targetPosition;
}


sf::View Camera::getCameraView()
{
	float aspectRatio = (float)gameData->window->getSize().x / gameData->window->getSize().y;
	float viewAreaHeight = position.z * tan(verticalFov * DEGREES_TO_RADIANS / 2) * 2;
	return sf::View(sf::Vector2f(position.x, position.y), sf::Vector2f(viewAreaHeight * aspectRatio, viewAreaHeight));
}


void Camera::updateTargetPosition()
{
	if (subject != nullptr)
	{
		sf::Vector2f playerCentre2D = subject->getPosition() + subject->getSize() * 0.5f;
		sf::Vector3f playerCentre3D(playerCentre2D.x, playerCentre2D.y, 0);
		targetPosition = playerCentre3D + followOffset;
	}
}