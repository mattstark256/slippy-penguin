#include "Button.h"

#include "Framework/Collision.h"
#include <iostream>

//#define FONT_FILE_PATH "font/Pixel NES.otf"
#define FONT_FILE_PATH "font/Pixel Gosub.otf"
#define TEXTURE_FILE_PATH "gfx/Button.png"
#define BUTTON_SIZE sf::Vector2f(256, 64)
#define DEFAULT_TEXTURE_RECT sf::IntRect(0, 0, 64, 16)
#define HOVER_TEXTURE_RECT sf::IntRect(0, 16, 64, 16)
#define PRESSED_TEXTURE_RECT sf::IntRect(0, 32, 64, 16)
#define FONT_SIZE 30
#define TEXT_OUTLINE_THICKNESS 3
#define TEXT_CENTRE_OFFSET sf::Vector2f(0, 6)


Button::Button()
{
	setSize(BUTTON_SIZE);
	setOrigin(getSize() * 0.5f);
	setCollisionBox(sf::FloatRect(getSize().x * -0.5f, getSize().y * -0.5f, getSize().x, getSize().y));

	if (!font.loadFromFile(FONT_FILE_PATH))
	{
		std::cout << "Unable to load " << FONT_FILE_PATH << std::endl;
	}
	text.setFont(font);
	text.setCharacterSize(FONT_SIZE);
	text.setOutlineThickness(TEXT_OUTLINE_THICKNESS);

	if (!texture.loadFromFile(TEXTURE_FILE_PATH))
	{
		std::cout << "Unable to load " << TEXTURE_FILE_PATH << std::endl;
	}
	setTexture(&texture);
	setTextureRect(DEFAULT_TEXTURE_RECT);
}


Button::~Button()
{
}


void Button::setText(std::string _textString)
{
	textString = _textString;
	text.setString(textString);

	// Centre the origin
	text.setOrigin(sf::Vector2f(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2));
	text.setOrigin(text.getOrigin() + TEXT_CENTRE_OFFSET); // Seems like a vertical offset gives a better centre. This probably varies between font.
}


void Button::handleInput(float dt)
{
	released = false;
	bool mouseDown = input->isMouseLDown();
	sf::Vector2i mousePosition(input->getMouseX(), input->getMouseY());

	// Check the button state
	if (Collision::checkBoundingBox(this, mousePosition))
	{
		hovering = true;
		if (mouseDown && !mouseWasDown)
		{
			pressing = true;
		}
		if (!mouseDown && pressing)
		{
			pressing = false;
			released = true;
		}
	}
	else
	{
		hovering = false;
		pressing = false;
	}

	// Set texture based on the button state
	if (pressing) { setTextureRect(PRESSED_TEXTURE_RECT); }
	else if (hovering) { setTextureRect(HOVER_TEXTURE_RECT); }
	else { setTextureRect(DEFAULT_TEXTURE_RECT); }

	mouseWasDown = mouseDown;
}


void Button::update(float dt)
{
}


// This is necessary because the text should be rendered whenever the button is rendered.
void Button::render(sf::RenderWindow* window)
{
	window->draw(*this);
	window->draw(text);
}


// This is necessary because the text should be moved whenever the button is moved.
void Button::setPosition(sf::Vector2f position)
{
	GameObject::setPosition(position);
	text.setPosition(position);
}


// Returns true for 1 update once left mouse is released.
bool Button::wasPressed()
{
	return released;
}
