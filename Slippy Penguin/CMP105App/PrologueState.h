#pragma once
#include "MenuState.h"

#include "Button.h"


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

