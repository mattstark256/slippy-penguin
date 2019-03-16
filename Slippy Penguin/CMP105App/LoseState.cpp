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

	buttonContinue = new Button(gameData);
	buttonContinue->setText("Try again?");

	buttonQuit = new Button(gameData);
	buttonQuit->setText("Quit to menu");
}


LoseState::~LoseState()
{

}

void LoseState::handleInput(float dt)
{
	MenuState::handleInput(dt);

	buttonContinue->handleInput(dt);
	if (buttonContinue->wasPressed())
	{
		gameData->stateManager->replaceState(LevelLoader::loadLevel(level, gameData));
	}

	buttonQuit->handleInput(dt);
	if (buttonQuit->wasPressed())
	{
		gameData->stateManager->replaceState(new MainMenuState(gameData));
	}
}

void LoseState::update(float dt)
{
	MenuState::update(dt);

	textTitle.setPosition(windowCentre + sf::Vector2f(0, -140));
	textMessage.setPosition(windowCentre + sf::Vector2f(0, -40));
	buttonContinue->setPosition(windowCentre + sf::Vector2f(0, 60));
	buttonQuit->setPosition(windowCentre + sf::Vector2f(0, 140));
}

void LoseState::renderObjects()
{
	MenuState::renderObjects();

	gameData->window->draw(textTitle);
	gameData->window->draw(textMessage);
	buttonContinue->render();
	buttonQuit->render();
}
