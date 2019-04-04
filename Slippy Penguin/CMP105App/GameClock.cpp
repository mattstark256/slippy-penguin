#include "GameClock.h"


GameClock::GameClock()
{
}


GameClock::~GameClock()
{
}


float GameClock::getTime()
{
	return clock.getElapsedTime().asSeconds();
}
