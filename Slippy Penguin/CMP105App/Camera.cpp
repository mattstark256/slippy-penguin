#include "Camera.h"
#include "Camera.h"

#define DEGREES_TO_RADIANS 0.0174533


Camera::Camera(GameData* _gameData) : gameData(_gameData)
{
}


Camera::~Camera()
{
}


void Camera::update(float dt)
{
	updateTargetPosition();

	// Smoothly move towards the target position
	float lerpValue = dt * moveSpeed;
	position = position * (1 - lerpValue) + targetPosition * lerpValue;
}


// Move immediately to the target position, without smoothing
void Camera::jumpToTarget()
{
	updateTargetPosition();
	position = targetPosition;
}


// Generate a View based on the camera's position and field of view
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
		targetPosition = sf::Vector3f(subject->getPosition().x, subject->getPosition().y, 0) + followOffset;
	}
}