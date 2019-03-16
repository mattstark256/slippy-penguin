#include "FinalWinState.h"

#include "MainMenuState.h"



FinalWinState::FinalWinState(GameData* _gameData, int _level) : MenuState(_gameData), level(_level)
{
	textTitle.setString("Level " + std::to_string(level) + " complete!");
	gameData->fontSettings->applyTitleSettings(&textTitle);
	gameData->fontSettings->centreTextOrigin(&textTitle);

	textMessage.setString("You finished the game! Well done!");
	gameData->fontSettings->applyRegularSettings(&textMessage);
	gameData->fontSettings->centreTextOrigin(&textMessage);

	buttonContinue = new Button(gameData);
	buttonContinue->setText("Quit to menu");
}


FinalWinState::~FinalWinState()
{
}


void FinalWinState::handleInput(float dt)
{
	MenuState::handleInput(dt);

	buttonContinue->handleInput(dt);

	if (buttonContinue->wasPressed())
	{
		gameData->stateManager->replaceState(new MainMenuState(gameData));
	}
}


void FinalWinState::update(float dt)
{
	MenuState::update(dt);

	textTitle.setPosition(windowCentre + sf::Vector2f(0, -100));
	textMessage.setPosition(windowCentre + sf::Vector2f(0, 0));
	buttonContinue->setPosition(windowCentre + sf::Vector2f(0, 100));
}


void FinalWinState::renderObjects()
{
	MenuState::renderObjects();

	gameData->window->draw(textTitle);
	gameData->window->draw(textMessage);
	buttonContinue->render();
}