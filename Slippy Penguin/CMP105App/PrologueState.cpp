#include "PrologueState.h"

#include "TutorialState.h"
#include <iostream>
#define STORY_PANEL_FILE_PATH "gfx/StoryPanels.png"


PrologueState::PrologueState(GameData* _gameData) : MenuState(_gameData)
{
	if (!texture.loadFromFile(STORY_PANEL_FILE_PATH))
	{
		std::cout << "Unable to load " << STORY_PANEL_FILE_PATH << std::endl;
	}
	storyPanel.setTexture(&texture);
	storyPanel.setSize(sf::Vector2f(240, 160));
	storyPanel.setOrigin(sf::Vector2f(120, 80));

	textInstruction1.setString("Pippa the penguin leaves her family\nto find food for her chick.");
	gameData->fontSettings->applyRegularSettings(&textInstruction1);
	gameData->fontSettings->centreTextOrigin(&textInstruction1);

	startButton = new Button(gameData);
	startButton->setText("Continue");
}


PrologueState::~PrologueState()
{
}


void PrologueState::handleInput(float dt)
{
	MenuState::handleInput(dt);

	startButton->handleInput(dt);

	if (startButton->wasPressed())
	{
		gameData->stateManager->replaceState(new TutorialState(gameData));
	}
}


void PrologueState::update(float dt)
{
	MenuState::update(dt);

	storyPanel.setPosition(windowCentre + sf::Vector2f(0, -105));
	textInstruction1.setPosition(windowCentre + sf::Vector2f(0, 50));
	startButton->setPosition(windowCentre + sf::Vector2f(0, 160));

	// The story panel is a looping two frame animation
	int frame = (int)(gameData->gameClock->getTime() * 10) % 2;
	storyPanel.setTextureRect(sf::IntRect(0 + frame * 48, 0, 48, 32));
}


void PrologueState::renderObjects()
{
	MenuState::renderObjects();

	gameData->window->draw(storyPanel);
	gameData->window->draw(textInstruction1);
	startButton->render();
}