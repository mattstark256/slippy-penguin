#pragma once

#include <stack>

// Forward declaration is necessary here to prevent circular dependency (State.h includes GameData.h which includes StateManager.h)
class State;


// This class uses a stack to keep track of the application's states. For example, when the game is paused, the pause state is on top of the game state.
class StateManager
{
public:
	StateManager();
	~StateManager();

	void popState();
	void pushState(State* state);
	void replaceState(State* state);
	State* getCurrentState();

private:
	std::stack<State*> stateStack;
};

