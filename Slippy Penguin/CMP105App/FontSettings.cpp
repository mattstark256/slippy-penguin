#include "FontSettings.h"

#include <iostream>

#define FONT_FILE_PATH "font/Pixel Gosub.otf"
#define CHARACTER_SIZE_REGULAR 30
#define CHARACTER_SIZE_TITLE 50
#define OUTLINE_THICKNESS 3
#define TEXT_CENTRE_OFFSET sf::Vector2f(0, 6)


FontSettings::FontSettings()
{
	// Load the font
	if (!font.loadFromFile(FONT_FILE_PATH))
	{
		std::cout << "Unable to load font from " << FONT_FILE_PATH << std::endl;
	}
}


FontSettings::~FontSettings()
{
}


// Apply a style suitable for regular text.
void FontSettings::applyRegularSettings(sf::Text* text)
{
	text->setFont(font);
	text->setCharacterSize(CHARACTER_SIZE_REGULAR);
	text->setOutlineThickness(OUTLINE_THICKNESS);
}


// Apply a style suitable for title text.
void FontSettings::applyTitleSettings(sf::Text* text)
{
	text->setFont(font);
	text->setCharacterSize(CHARACTER_SIZE_TITLE);
	text->setOutlineThickness(OUTLINE_THICKNESS);
}


// Set the origin of the text to its centre.
void FontSettings::centreTextOrigin(sf::Text* text)
{
	text->setOrigin(sf::Vector2f(text->getGlobalBounds().width / 2, text->getGlobalBounds().height / 2));
	text->setOrigin(text->getOrigin() + TEXT_CENTRE_OFFSET); // A small vertical offset gives a better centre. The offset amount probably depends on the font.
}

