#include "CreditsState.h"

#include "MainMenuState.h"


CreditsState::CreditsState(GameData* _gameData) : MenuState(_gameData)
{
	textTitle.setString("Credits");
	gameData->fontSettings->applyTitleSettings(&textTitle);
	gameData->fontSettings->centreTextOrigin(&textTitle);

	textCredit1.setString("Slippy Penguin was made by Matt Stark\n\nFont:\nPixel Gosub - Pixel Sagas (Neale and Shayna Davidson)\n\nMusic:\nSnowman (Earthbound) - Keiichi Suzuki and Hirokazu Tanaka\n\nSound effects:\nThe Essential Retro Video Game Sound Effects Collection - Juhani Junkala");
	gameData->fontSettings->applyRegularSettings(&textCredit1);
	textCredit1.setCharacterSize(20);
	gameData->fontSettings->centreTextOrigin(&textCredit1);

	mainMenuButton = new Button(gameData);
	mainMenuButton->setText("Back to menu");
}


CreditsState::~CreditsState()
{
}


void CreditsState::handleInput(float dt)
{
	MenuState::handleInput(dt);

	mainMenuButton->handleInput(dt);
	if (mainMenuButton->wasPressed())
	{
		gameData->stateManager->replaceState(new MainMenuState(gameData));
	}
}


void CreditsState::update(float dt)
{
	MenuState::update(dt);

	textTitle.setPosition(windowCentre + sf::Vector2f(0, -200));
	textCredit1.setPosition(windowCentre + sf::Vector2f(0, 0));
	mainMenuButton->setPosition(windowCentre + sf::Vector2f(0, 200));
}


void CreditsState::renderObjects()
{
	MenuState::renderObjects();

	gameData->window->draw(textTitle);
	gameData->window->draw(textCredit1);
	mainMenuButton->render();
}
