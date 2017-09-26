#pragma once

#include "SFML/Graphics.hpp"

class TextBox
{
	

public:
	TextBox();
	TextBox(sf::String str, sf::Font& f, int larghezza, int lunghezza, bool scaled = false); //TODO pass size and position
	sf::Text getText() const;

	sf::RectangleShape rect;
	sf::Text text;
	sf::View view;

	~TextBox();
};

