#include "MainMenuState.h"

#include <iostream>
#include "PrologueState.h"
#include "PreLevelState.h"
#include "CreditsState.h"


MainMenuState::MainMenuState(GameData* _gameData) : MenuState(_gameData)
{
	textTitle.setString("Slippy Penguin");
	gameData->fontSettings->applyTitleSettings(&textTitle);
	gameData->fontSettings->centreTextOrigin(&textTitle);

	// There should only be a "Continue" button if the player has save data
	if (gameData->playerData->saveDataExists())
	{
		newGameButton = new Button(gameData);
		newGameButton->setText("New game");
		continueButton = new Button(gameData);
		continueButton->setText("Continue");
	}
	else
	{
		newGameButton = new Button(gameData);
		newGameButton->setText("Start game");
	}

	creditsButton = new Button(gameData);
	creditsButton->setText("Credits");

	quitButton = new Button(gameData);
	quitButton->setText("Quit");
}


MainMenuState::~MainMenuState()
{
}


void MainMenuState::handleInput(float dt)
{
	MenuState::handleInput(dt);

	newGameButton->handleInput(dt);
	if (newGameButton->wasPressed())
	{
		// Delete any save data and start the tutorial
		gameData->playerData->resetCompletedLevels();
		gameData->stateManager->replaceState(new PrologueState(gameData));
	}

	if (gameData->playerData->saveDataExists())
	{
		continueButton->handleInput(dt);
		if (continueButton->wasPressed())
		{
			// Start the level above the highest completed level
			gameData->stateManager->replaceState(new PreLevelState(gameData, gameData->playerData->getCompletedLevels() + 1));
		}
	}

	creditsButton->handleInput(dt);
	if (creditsButton->wasPressed())
	{
		// Go to the credits screen
		gameData->stateManager->replaceState(new CreditsState(gameData));
	}

	quitButton->handleInput(dt);
	if (quitButton->wasPressed())
	{
		// Quit the application
		gameData->window->close();
	}
}


void MainMenuState::update(float dt)
{
	MenuState::update(dt);

	// The menu needs to be arranged differently to fit the "Continue" button
	if (gameData->playerData->saveDataExists())
	{
		textTitle.setPosition(windowCentre + sf::Vector2f(0, -180));
		continueButton->setPosition(windowCentre + sf::Vector2f(0, -80));
		newGameButton->setPosition(windowCentre + sf::Vector2f(0, 0));
		creditsButton->setPosition(windowCentre + sf::Vector2f(0, 80));
		quitButton->setPosition(windowCentre + sf::Vector2f(0, 160));
	}
	else
	{
		textTitle.setPosition(windowCentre + sf::Vector2f(0, -140));
		newGameButton->setPosition(windowCentre + sf::Vector2f(0, -40));
		creditsButton->setPosition(windowCentre + sf::Vector2f(0, 40));
		quitButton->setPosition(windowCentre + sf::Vector2f(0, 120));
	}
}


void MainMenuState::renderObjects()
{
	MenuState::renderObjects();

	gameData->window->draw(textTitle);
	newGameButton->render();
	creditsButton->render();
	quitButton->render();

	if (gameData->playerData->saveDataExists())
	{
		continueButton->render();
	}
}