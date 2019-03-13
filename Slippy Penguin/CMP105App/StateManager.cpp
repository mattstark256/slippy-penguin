#include "StateManager.h"

#include <iostream>


StateManager::StateManager()
{
}


StateManager::~StateManager()
{
}


void StateManager::popState()
{
	if (stateStack.empty())
	{
		std::cout << "Unable to pop state because stateStack is empty!";
	}
	else
	{
		stateStack.pop();
	}
}


void StateManager::pushState(State* state)
{
	stateStack.push(state);
}


void StateManager::replaceState(State* state)
{
	popState();
	pushState(state);
}


State * StateManager::getCurrentState()
{
	return stateStack.top();
}
