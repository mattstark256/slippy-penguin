// Main
// Entry point of the application.
// Handles window creation and window events.
// Contains the game loop, updates input class and contains the level objects.
// @author Paul Robertson

#include <iostream>

#include "GameData.h"
#include "StateManager.h"
#include "MainMenuState.h"

int main()
{
	// Initialize gameData
	GameData* gameData = new GameData();
	gameData->window = new sf::RenderWindow(sf::VideoMode(1200, 675), "CMP105");;
	gameData->input = new Input();
	gameData->stateManager = new StateManager();

	// Create the first state
	gameData->stateManager->pushState(new MainMenuState(gameData));

	// Initialise objects for delta time
	sf::Clock clock;
	float deltaTime;

	// Game Loop
	while (gameData->window->isOpen())
	{
		// Handle window events.
		sf::Event event;
		sf::RenderWindow* window = gameData->window;
		Input* input = gameData->input;
		while (window->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window->close();
				break;
			case sf::Event::Resized:
				window->setView(sf::View(sf::FloatRect(0.f, 0.f, (float)event.size.width, (float)event.size.height)));
				break;
			case sf::Event::KeyPressed:
				// update input class
				input->setKeyDown(event.key.code);
				break;
			case sf::Event::KeyReleased:
				//update input class
				input->setKeyUp(event.key.code);
				break;
			case sf::Event::MouseMoved:
				//update input class
				input->setMousePosition(event.mouseMove.x, event.mouseMove.y);
				break;
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					//update input class
					input->setMouseLDown(true);
				}
				else if (event.mouseButton.button == sf::Mouse::Right)
				{
					input->setMouseRDown(true);
				}
				break;
			case sf::Event::MouseButtonReleased:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					//update input class
					input->setMouseLDown(false);
				}
				else if (event.mouseButton.button == sf::Mouse::Right)
				{
					input->setMouseRDown(false);
				}
				break;
			default:
				// don't handle other events
				break;
			}
		}

		// Calculate delta time. How much time has passed 
		// since it was last calculated (in seconds) and restart the clock.
		deltaTime = clock.restart().asSeconds();

		// Call standard game loop functions (input, update and render)
		State* state = gameData->stateManager->getCurrentState();
		state->handleInput(deltaTime);
		state->update(deltaTime);
		state->render();
	}
}

