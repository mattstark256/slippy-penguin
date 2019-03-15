#include "PreLevelState.h"

#include "LevelLoader.h"


PreLevelState::PreLevelState(GameData* _gameData, int _level) : MenuState(_gameData), level(_level)
{
	textTitle.setString("Level " + std::to_string(level));
	gameData->fontSettings->applyTitleSettings(&textTitle);
	gameData->fontSettings->centreTextOrigin(&textTitle);

	buttonStart = new Button(gameData);
	buttonStart->setText("Start!");

}


PreLevelState::~PreLevelState()
{

}


void PreLevelState::handleInput(float dt)
{
	MenuState::handleInput(dt);

	buttonStart->handleInput(dt);

	if (buttonStart->wasPressed())
	{
		gameData->stateManager->replaceState(LevelLoader::loadLevel(level, gameData));
	}
}


void PreLevelState::update(float dt)
{
	MenuState::update(dt);

	textTitle.setPosition(windowCentre + sf::Vector2f(0, -50));
	buttonStart->setPosition(windowCentre + sf::Vector2f(0, 50));
}


void PreLevelState::renderObjects()
{
	MenuState::renderObjects();

	gameData->window->draw(textTitle);
	buttonStart->render();
}
