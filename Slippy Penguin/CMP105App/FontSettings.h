#pragma once

#include <SFML/Graphics.hpp>


// Rather than loading the font and applying font style inside every state that contains text, I do it all in this class.
class FontSettings
{
public:
	FontSettings();
	~FontSettings();

	void applyRegularSettings(sf::Text* text);
	void applyTitleSettings(sf::Text* text);
	void centreTextOrigin(sf::Text* text);

private:
	sf::Font font;
};

