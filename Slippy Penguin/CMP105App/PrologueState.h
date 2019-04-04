#pragma once
#include "MenuState.h"

#include "Button.h"


// This is the screen the player sees when starting a new game. It includes story text and an animation.
class PrologueState :
	public MenuState
{
public:
	PrologueState(GameData* gameData);
	~PrologueState();

	virtual void handleInput(float dt);
	virtual void update(float dt);

protected:
	virtual void renderObjects();

	sf::Text textInstruction1;
	Button* startButton;
	sf::Texture texture;
	GameObject storyPanel;
};

