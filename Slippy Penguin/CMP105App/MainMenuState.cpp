#include "MainMenuState.h"

#include <iostream>
#include "TutorialState.h"


MainMenuState::MainMenuState(GameData* gameData) : MenuState(gameData)
{
	startButton.setText("Start game");
	startButton.setInput(gameData->input);
}


MainMenuState::~MainMenuState()
{
}


void MainMenuState::handleInput(float dt)
{
	startButton.handleInput(dt);

	if (startButton.wasPressed())
	{
		std::cout << "button pressed\n";
		gameData->stateManager->replaceState(new TutorialState(gameData));
	}
}


void MainMenuState::update(float dt)
{
	startButton.setPosition((sf::Vector2f)gameData->window->getSize() * 0.5f);
}


void MainMenuState::renderObjects()
{
	MenuState::renderObjects();

	startButton.render(gameData->window);
}