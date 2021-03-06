// Main
// Entry point of the application.
// Handles window creation and window events.
// Contains the game loop, updates input class and contains the level objects.
// @author Paul Robertson

#include <iostream>

#include "GameData.h"
#include "MainMenuState.h"

int main()
{
	// Initialize gameData
	GameData* gameData = new GameData();
	gameData->window = new sf::RenderWindow(sf::VideoMode(1200, 675), "Frozen Foods");;
	gameData->input = new Input();
	gameData->stateManager = new StateManager();
	gameData->playerData = new PlayerData();
	gameData->fontSettings = new FontSettings();
	gameData->gameClock = new GameClock();
	gameData->audioManager = new AudioManager();

	// Set up audio
	gameData->audioManager->addMusic("sfx/Snowman clipped.ogg", "snowman");
	gameData->audioManager->addSound("sfx/Fanfare.ogg", "win");
	gameData->audioManager->addSound("sfx/Lose.ogg", "lose");
	gameData->audioManager->addSound("sfx/Eat.wav", "eat fish");
	gameData->audioManager->addSound("sfx/Scream.wav", "scream");
	gameData->audioManager->addSound("sfx/Button press.wav", "button");
	gameData->audioManager->getSound("button")->setVolume(50);

	// Starting the music from the beginning every time a level starts gets repetitive so instead I pause and play it.
	gameData->audioManager->playMusicbyName("snowman");
	gameData->audioManager->getMusic()->pause();
	gameData->audioManager->getMusic()->setVolume(30);

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

		// Calculate delta time (seconds since it was last calculated) and restart the clock.
		deltaTime = clock.restart().asSeconds();

		// Call standard game loop functions (input, update and render)
		State* state = gameData->stateManager->getCurrentState();
		state->handleInput(deltaTime);
		state->update(deltaTime);
		state->render();
	}
}

