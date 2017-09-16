#pragma once

#include "SFML/Graphics.hpp"

class TextBox
{
	

public:
	TextBox(sf::String str, sf::Font& f, int larghezza, int lunghezza); //TODO pass size and position
	sf::Text getText() const;

	sf::RectangleShape rect;
	sf::Text text;

	~TextBox();
};

