#pragma once
#include "Framework/GameObject.h"
#include "Framework/Input.h"
#include <string>


// This class is used for all of the game's clickable buttons. It has a text child object.
class Button :
	public GameObject
{
public:
	Button();
	~Button();

	void setText(std::string _textString);

	void handleInput(float dt);
	void update(float dt);
	void render(sf::RenderWindow* window);
	void setPosition(sf::Vector2f position);

	bool wasPressed();

private:
	sf::Texture texture;
	std::string textString;
	sf::Font font;
	sf::Text text;
	bool mouseWasDown = false;
	bool hovering = false;
	bool pressing = false;
	bool released = false;
};

