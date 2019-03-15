#pragma once

// This class holds user data such as progress and settings.
// If in future I add a way of saving data so it isn't lost between sessions, PlayerData will be an interface for that.
class PlayerData
{
public:
	PlayerData();
	~PlayerData();

	int getCompletedLevels();
	void updateCompletedLevels(int completedLevel);
	void resetCompletedLevels();

private:
	int completedLevels = 0;
};
