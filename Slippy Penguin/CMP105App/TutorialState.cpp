#include "TutorialState.h"

#include "PreLevelState.h"


TutorialState::TutorialState(GameData* _gameData) : MenuState(_gameData)
{
	textTitle.setString("How to play");
	gameData->fontSettings->applyTitleSettings(&textTitle);
	gameData->fontSettings->centreTextOrigin(&textTitle);

	textInstruction1.setString("- Move with arrow keys or WASD\n- Collect all the fish\n- Don't get eaten");
	gameData->fontSettings->applyRegularSettings(&textInstruction1);
	gameData->fontSettings->centreTextOrigin(&textInstruction1);

	startButton = new Button(gameData);
	startButton->setText("Got it");

}


TutorialState::~TutorialState()
{
}


void TutorialState::handleInput(float dt)
{
	MenuState::handleInput(dt);

	startButton->handleInput(dt);

	if (startButton->wasPressed())
	{
		gameData->stateManager->replaceState(new PreLevelState(gameData, 1));
	}
}


void TutorialState::update(float dt)
{
	MenuState::update(dt);

	textTitle.setPosition(windowCentre + sf::Vector2f(0, -130)); 
	textInstruction1.setPosition(windowCentre + sf::Vector2f(0, 0));
	startButton->setPosition(windowCentre + sf::Vector2f(0, 130));
}


void TutorialState::renderObjects()
{
	MenuState::renderObjects();

	gameData->window->draw(textTitle);
	gameData->window->draw(textInstruction1);
	startButton->render();
}
