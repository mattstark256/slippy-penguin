#include "PlayerData.h"



PlayerData::PlayerData()
{
}


PlayerData::~PlayerData()
{
}


int PlayerData::getCompletedLevels()
{
	return completedLevels;
}


// If the player's progress is less the stored value, update it. This means completing a level can never decrease the player's progress.
void PlayerData::updateCompletedLevels(int completedLevel)
{
	if (completedLevels < completedLevel)
	{
		completedLevels = completedLevel;
	}
}


// This is used when the player starts a new game to reset progress.
void PlayerData::resetCompletedLevels()
{
	completedLevels = 0;
}