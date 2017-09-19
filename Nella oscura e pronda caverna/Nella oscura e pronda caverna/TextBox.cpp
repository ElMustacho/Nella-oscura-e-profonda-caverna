#include "TextBox.h"
#include <iostream>


TextBox::TextBox(sf::String str, sf::Font& f, int larghezza, int lunghezza, bool scaled) //TODO resize with window
{
	if (scaled)
	{
		auto posX = larghezza * 0.05;
		auto posY = lunghezza * 0.80;
		auto sizeX = larghezza * 0.90;
		auto sizeY = lunghezza * 0.15;

		rect.setFillColor(sf::Color(0, 0, 0, 120));
		rect.setOutlineThickness(2);
		rect.setOutlineColor(sf::Color(230, 138, 0, 255));
		rect.setPosition(posX, posY);
		rect.setSize(sf::Vector2f(sizeX, sizeY));

		text.setFont(f);
		text.setString(str);
		text.setCharacterSize(14);
		text.setPosition(posX + 5, posY + 5);
	}
	else
	{
		auto posX = larghezza * 0.01; // 
		auto posY = lunghezza * 0.02; //
		auto sizeX = larghezza * 0.99; // 
		auto sizeY = lunghezza * 0.98; // 

		rect.setFillColor(sf::Color(0, 0, 0, 120));
		rect.setOutlineThickness(2);
		rect.setOutlineColor(sf::Color(230, 138, 0, 255));
		rect.setPosition(posX, posY);
		rect.setSize(sf::Vector2f(sizeX, sizeY));

		text.setFont(f);
		text.setString(str);
		text.setCharacterSize(14);
		text.setPosition(posX + 5, posY + 5);
	}
}


sf::Text TextBox::getText() const
{
	return this->text;
}

TextBox::~TextBox()
{
}
