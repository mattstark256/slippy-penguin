#pragma once

#include <SFML/Graphics.hpp>


// This class is used to measure the time since the application started. It's currently only used for keeping the wallpaper animation continuous between states.
class GameClock
{
public:
	GameClock();
	~GameClock();

	float getTime();

private:
	sf::Clock clock;
};

