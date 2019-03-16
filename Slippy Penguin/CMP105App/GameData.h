#pragma once

#include <SFML/Graphics.hpp>
#include "Framework/Input.h"
#include "StateManager.h"
#include "PlayerData.h"
#include "FontSettings.h"
#include "GameClock.h"


// This struct is used to contain pointers to objects that should persist throughout execution, such as the Input object.
struct GameData
{
	sf::RenderWindow* window;
	Input* input;
	StateManager* stateManager;
	PlayerData* playerData;
	FontSettings* fontSettings;
	GameClock* gameClock;
};