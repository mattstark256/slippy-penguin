#include "WinState.h"

#include "PreLevelState.h"



WinState::WinState(GameData* _gameData, int _level) : MenuState(_gameData), level(_level)
{
	textTitle.setString("Level " + std::to_string(level) + " complete!");
	gameData->fontSettings->applyTitleSettings(&textTitle);
	gameData->fontSettings->centreTextOrigin(&textTitle);

	buttonContinue = new Button(gameData);
	buttonContinue->setText("Continue");
}


WinState::~WinState()
{
}


void WinState::handleInput(float dt)
{
	MenuState::handleInput(dt);

	buttonContinue->handleInput(dt);

	if (buttonContinue->wasPressed())
	{
		gameData->stateManager->replaceState(new PreLevelState(gameData, level + 1));
	}
}


void WinState::update(float dt)
{
	MenuState::update(dt);

	textTitle.setPosition(windowCentre + sf::Vector2f(0, -50));
	buttonContinue->setPosition(windowCentre + sf::Vector2f(0, 50));
}


void WinState::renderObjects()
{
	MenuState::renderObjects();

	gameData->window->draw(textTitle);
	buttonContinue->render();
}
