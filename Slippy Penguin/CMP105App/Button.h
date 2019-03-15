#pragma once
#include "Framework/GameObject.h"

#include "Framework/Input.h"
#include <string>
#include "GameData.h"


// This class is used for all of the game's clickable buttons. It has a text child object.
class Button :
	public GameObject
{
public:
	Button(GameData* gameData);
	~Button();

	void setText(std::string _textString);

	void handleInput(float dt);
	void update(float dt);
	void render();
	void setPosition(sf::Vector2f position);

	bool wasPressed();

private:
	GameData* gameData;
	sf::Texture texture;
	std::string textString;
	sf::Text text;
	bool mouseWasDown = false;
	bool hovering = false;
	bool pressing = false;
	bool released = false;
};

