#include "Button.h"

#include "Framework/Collision.h"
#include <iostream>

#define TEXTURE_FILE_PATH "gfx/Button.png"
#define BUTTON_SIZE sf::Vector2f(256, 64)
#define DEFAULT_TEXTURE_RECT sf::IntRect(0, 0, 64, 16)
#define HOVER_TEXTURE_RECT sf::IntRect(0, 16, 64, 16)
#define PRESSED_TEXTURE_RECT sf::IntRect(0, 32, 64, 16)


Button::Button(GameData* _gameData) : gameData(_gameData)
{
	input = gameData->input;

	setSize(BUTTON_SIZE);
	// Centre the origin
	setOrigin(getSize() * 0.5f);
	setCollisionBox(sf::FloatRect(getSize().x * -0.5f, getSize().y * -0.5f, getSize().x, getSize().y));

	gameData->fontSettings->applyRegularSettings(&text);

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
	gameData->fontSettings->centreTextOrigin(&text);
}


void Button::handleInput(float dt)
{
	released = false;
	bool mouseDown = input->isMouseLDown();
	bool hovering = Collision::checkBoundingBox(this, sf::Vector2i(input->getMouseX(), input->getMouseY()));

	if (hovering)
	{
		// If a press has begun
		if (mouseDown && !mouseWasDown)
		{
			pressed = true;
			gameData->audioManager->playSoundbyName("button");
		}
		// If a press has ended
		if (!mouseDown && pressed)
		{
			pressed = false;
			released = true;
		}
	}
	else
	{
		// If the mouse is moved off the button mid-press the press gets cancelled
		pressed = false;
	}

	// Set texture based on the button state
	if (pressed) { setTextureRect(PRESSED_TEXTURE_RECT); }
	else if (hovering) { setTextureRect(HOVER_TEXTURE_RECT); }
	else { setTextureRect(DEFAULT_TEXTURE_RECT); }

	mouseWasDown = mouseDown;
}


void Button::update(float dt)
{
}


// This is necessary because the text should be rendered whenever the button is rendered.
void Button::render()
{
	gameData->window->draw(*this);
	gameData->window->draw(text);
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
