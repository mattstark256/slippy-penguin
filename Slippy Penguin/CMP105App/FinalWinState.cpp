#include "FinalWinState.h"

#include "MainMenuState.h"
#include <iostream>
#define STORY_PANEL_FILE_PATH "gfx/StoryPanels.png"


FinalWinState::FinalWinState(GameData* _gameData, int _level) : MenuState(_gameData), level(_level)
{
	textTitle.setString("Level " + std::to_string(level) + " complete!");
	gameData->fontSettings->applyTitleSettings(&textTitle);
	gameData->fontSettings->centreTextOrigin(&textTitle);

	textMessage.setString("You finished the game! Well done!\nPippa returns home and regurgitates\nthe fish for her chick.");
	gameData->fontSettings->applyRegularSettings(&textMessage);
	gameData->fontSettings->centreTextOrigin(&textMessage);

	if (!texture.loadFromFile(STORY_PANEL_FILE_PATH))
	{
		std::cout << "Unable to load " << STORY_PANEL_FILE_PATH << std::endl;
	}
	storyPanel.setTexture(&texture);
	storyPanel.setSize(sf::Vector2f(240, 160));
	storyPanel.setOrigin(sf::Vector2f(120, 80));

	buttonContinue = new Button(gameData);
	buttonContinue->setText("Quit to menu");

	gameData->audioManager->playSoundbyName("win");
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

	textTitle.setPosition(windowCentre + sf::Vector2f(0, -225));
	textMessage.setPosition(windowCentre + sf::Vector2f(0, -105));
	storyPanel.setPosition(windowCentre + sf::Vector2f(0, 65));
	buttonContinue->setPosition(windowCentre + sf::Vector2f(0, 225));

	// The story panel is a looping two frame animation
	int frame = (int)(gameData->gameClock->getTime() * 10) % 2;
	storyPanel.setTextureRect(sf::IntRect(0 + frame * 48, 32, 48, 32));
}


void FinalWinState::renderObjects()
{
	MenuState::renderObjects();

	gameData->window->draw(textTitle);
	gameData->window->draw(textMessage);
	gameData->window->draw(storyPanel);
	buttonContinue->render();
}