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


bool PlayerData::saveDataExists()
{
	return completedLevels != 0;
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
// It's currently also used when they complete the last level so that the main menu no longer shows the "Continue" button.
void PlayerData::resetCompletedLevels()
{
	completedLevels = 0;
}
