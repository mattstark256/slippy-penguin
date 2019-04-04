#include "PauseMenuState.h"

#include "LevelLoader.h"
#include "MainMenuState.h"
#include "PreLevelState.h"
#include <iostream>
#define BACKGROUND_TEXTURE_FILE_PATH "gfx/PauseMenuBackground.png"


PauseMenuState::PauseMenuState(GameData* _gameData, int _level, int score, int targetScore, LevelState* _pausedLevel) :
	State(_gameData), level(_level), pausedLevel(_pausedLevel)
{
	gameData->window->setMouseCursorVisible(true);

	if (!backgroundTexture.loadFromFile(BACKGROUND_TEXTURE_FILE_PATH))
	{
		std::cout << "Unable to load " << BACKGROUND_TEXTURE_FILE_PATH << std::endl;
	}
	menuBackground.setTexture(&backgroundTexture);
	menuBackground.setSize(sf::Vector2f(640, 496));
	menuBackground.setOrigin(sf::Vector2f(320, 248));

	textTitle.setString("Paused");
	gameData->fontSettings->applyTitleSettings(&textTitle);
	gameData->fontSettings->centreTextOrigin(&textTitle);

	// Display the level number and current score
	textScore.setString("Level " + std::to_string(level) + ": " + std::to_string(score) + "/" + std::to_string(targetScore) + " fish collected");
	gameData->fontSettings->applyRegularSettings(&textScore);
	gameData->fontSettings->centreTextOrigin(&textScore);

	buttonResume = new Button(gameData);
	buttonResume->setText("Resume");

	buttonRestart = new Button(gameData);
	buttonRestart->setText("Restart level");

	buttonQuit = new Button(gameData);
	buttonQuit->setText("Quit to menu");

	gameData->audioManager->getMusic()->pause();
}


PauseMenuState::~PauseMenuState()
{
}


void PauseMenuState::handleInput(float dt)
{
	State::handleInput(dt);

	// The player can close the pause menu using either the "Resume" button or by pressing escape.
	buttonResume->handleInput(dt);
	if (buttonResume->wasPressed())
	{
		gameData->audioManager->getMusic()->play();
		gameData->stateManager->popState();
	}
	if (gameData->input->isKeyDown(sf::Keyboard::Escape))
	{
		gameData->input->setKeyUp(sf::Keyboard::Escape);
		gameData->audioManager->getMusic()->play();
		gameData->stateManager->popState();
	}

	buttonRestart->handleInput(dt);
	if (buttonRestart->wasPressed())
	{
		// Reload the paused level
		gameData->stateManager->popState();
		gameData->stateManager->replaceState(new PreLevelState(gameData, level));
	}

	buttonQuit->handleInput(dt);
	if (buttonQuit->wasPressed())
	{
		// Go to the main menu
		gameData->stateManager->popState();
		gameData->stateManager->replaceState(new MainMenuState(gameData));
	}
}


void PauseMenuState::update(float dt)
{
	State::update(dt);

	menuBackground.setPosition(windowCentre);
	textTitle.setPosition(windowCentre + sf::Vector2f(0, -170));
	textScore.setPosition(windowCentre + sf::Vector2f(0, -90));
	buttonResume->setPosition(windowCentre + sf::Vector2f(0, 0));
	buttonRestart->setPosition(windowCentre + sf::Vector2f(0, 80));
	buttonQuit->setPosition(windowCentre + sf::Vector2f(0, 160));
}


void PauseMenuState::renderObjects()
{
	State::renderObjects();

	pausedLevel->renderObjects();

	gameData->window->draw(menuBackground);
	gameData->window->draw(textTitle);
	gameData->window->draw(textScore);
	buttonResume->render();
	buttonRestart->render();
	buttonQuit->render();
}