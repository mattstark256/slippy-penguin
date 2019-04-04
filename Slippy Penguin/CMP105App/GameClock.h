#pragma once

#include <SFML/Graphics.hpp>


// This class is used to measure the time since the application started. It's used for things like keeping the menu background animation continuous between menu screens.
class GameClock
{
public:
	GameClock();
	~GameClock();

	float getTime();

private:
	sf::Clock clock;
};

