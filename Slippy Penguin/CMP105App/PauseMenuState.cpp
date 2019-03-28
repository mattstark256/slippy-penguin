#include "PauseMenuState.h"

#include "LevelLoader.h"
#include "MainMenuState.h"
#include "PreLevelState.h"


PauseMenuState::PauseMenuState(GameData* _gameData, int _level, int score, int targetScore, LevelState* _pausedLevel) :
	State(_gameData), level(_level), pausedLevel(_pausedLevel)
{
	gameData->window->setMouseCursorVisible(true);

	menuBackground.setSize(sf::Vector2f(650, 500));
	menuBackground.setOrigin(sf::Vector2f(325, 250));
	menuBackground.setFillColor(sf::Color(0, 0, 0, 200));

	textTitle.setString("Pause menu");
	gameData->fontSettings->applyTitleSettings(&textTitle);
	gameData->fontSettings->centreTextOrigin(&textTitle);

	textScore.setString("Level " + std::to_string(level) + ": " + std::to_string(score) + "/" + std::to_string(targetScore) + " fish collected");
	gameData->fontSettings->applyRegularSettings(&textScore);
	gameData->fontSettings->centreTextOrigin(&textScore);

	buttonResume = new Button(gameData);
	buttonResume->setText("Resume");

	buttonRestart = new Button(gameData);
	buttonRestart->setText("Restart level");

	buttonQuit = new Button(gameData);
	buttonQuit->setText("Quit to menu");
}


PauseMenuState::~PauseMenuState()
{
}


void PauseMenuState::handleInput(float dt)
{
	State::handleInput(dt);

	buttonResume->handleInput(dt);
	buttonRestart->handleInput(dt);
	buttonQuit->handleInput(dt);

	// The player can close the pause menu using either the "Resume" button or by pressing escape.
	if (buttonResume->wasPressed())
	{
		gameData->stateManager->popState();
	}
	if (gameData->input->isKeyDown(sf::Keyboard::Escape))
	{
		gameData->input->setKeyUp(sf::Keyboard::Escape);
		gameData->stateManager->popState();
	}

	if (buttonRestart->wasPressed())
	{
		gameData->stateManager->popState();
		gameData->stateManager->replaceState(new PreLevelState(gameData, level));
	}

	if (buttonQuit->wasPressed())
	{
		gameData->stateManager->popState();
		gameData->stateManager->replaceState(new MainMenuState(gameData));
	}
}


void PauseMenuState::update(float dt)
{
	State::update(dt);

	menuBackground.setPosition(windowCentre);
	textTitle.setPosition(windowCentre + sf::Vector2f(0, -160));
	textScore.setPosition(windowCentre + sf::Vector2f(0, -80));
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