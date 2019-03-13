#pragma once

#include <SFML/Graphics.hpp>
#include "Framework/Input.h"
#include "StateManager.h"


// This struct is used to contain pointers to objects that should persist throughout execution, such as the Input object.
struct GameData
{
	sf::RenderWindow* window;
	Input* input;
	StateManager* stateManager;
};