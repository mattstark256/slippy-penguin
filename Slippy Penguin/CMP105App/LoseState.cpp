#include "LoseState.h"

#include "LevelLoader.h"
#include "MainMenuState.h"


LoseState::LoseState(GameData* _gameData, int _level, std::string loseMessage) : MenuState(_gameData), level(_level)
{
	textTitle.setString("Oops!");
	gameData->fontSettings->applyTitleSettings(&textTitle);
	gameData->fontSettings->centreTextOrigin(&textTitle);

	textMessage.setString(loseMessage);
	gameData->fontSettings->applyRegularSettings(&textMessage);
	gameData->fontSettings->centreTextOrigin(&textMessage);

	buttonRetry = new Button(gameData);
	buttonRetry->setText("Try again?");

	buttonQuit = new Button(gameData);
	buttonQuit->setText("Quit to menu");
}


LoseState::~LoseState()
{

}


void LoseState::handleInput(float dt)
{
	MenuState::handleInput(dt);

	buttonRetry->handleInput(dt);
	if (buttonRetry->wasPressed())
	{
		// Reload the level
		gameData->stateManager->replaceState(LevelLoader::loadLevel(level, gameData));
	}

	buttonQuit->handleInput(dt);
	if (buttonQuit->wasPressed())
	{
		// Quit to the main menu
		gameData->stateManager->replaceState(new MainMenuState(gameData));
	}
}


void LoseState::update(float dt)
{
	MenuState::update(dt);

	textTitle.setPosition(windowCentre + sf::Vector2f(0, -140));
	textMessage.setPosition(windowCentre + sf::Vector2f(0, -40));
	buttonRetry->setPosition(windowCentre + sf::Vector2f(0, 60));
	buttonQuit->setPosition(windowCentre + sf::Vector2f(0, 140));
}


void LoseState::renderObjects()
{
	MenuState::renderObjects();

	gameData->window->draw(textTitle);
	gameData->window->draw(textMessage);
	buttonRetry->render();
	buttonQuit->render();
}