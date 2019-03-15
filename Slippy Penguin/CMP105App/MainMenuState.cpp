#include "MainMenuState.h"

#include <iostream>
#include "TutorialState.h"


MainMenuState::MainMenuState(GameData* _gameData) : MenuState(_gameData)
{
	startButton = new Button(gameData);
	startButton->setText("Start game");
}


MainMenuState::~MainMenuState()
{
}


void MainMenuState::handleInput(float dt)
{
	MenuState::handleInput(dt);

	startButton->handleInput(dt);

	if (startButton->wasPressed())
	{
		gameData->stateManager->replaceState(new TutorialState(gameData));
	}
}


void MainMenuState::update(float dt)
{
	MenuState::update(dt);

	startButton->setPosition(windowCentre);
}


void MainMenuState::renderObjects()
{
	MenuState::renderObjects();

	startButton->render();
}