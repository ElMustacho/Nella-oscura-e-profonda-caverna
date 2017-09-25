#include "TextBox.h"
#include <iostream>


TextBox::TextBox()
{
	auto larghezza = 15*32;
	auto lunghezza = 10*32;
	auto posX = larghezza * 0.01;
	auto posY = lunghezza * 0.02;
	auto sizeX = larghezza * 0.99;
	auto sizeY = lunghezza * 0.98;

	rect.setFillColor(sf::Color(0, 0, 0, 120));
	rect.setOutlineThickness(2);
	rect.setOutlineColor(sf::Color(230, 138, 0, 255));
	rect.setPosition(posX, posY);
	rect.setSize(sf::Vector2f(sizeX, sizeY));

	sf::String str("Something wrong\n");

	sf::Font f;
	if (f.loadFromFile("arial.ttf"))
	{
		//err...
	}

	text.setFont(f);
	text.setString(str);
	text.setCharacterSize(14);
	text.setPosition(posX + 5, posY + 5);
}

TextBox::TextBox(sf::String str, sf::Font& f, int larghezza, int lunghezza, bool scaled) //TODO resize with window
{
	auto posX = larghezza;
	auto posY = lunghezza;
	auto sizeX = larghezza;
	auto sizeY = lunghezza;

	if (scaled)
	{
		posX *= 0.05;
		posY *= 0.80;
		sizeX *= 0.90;
		sizeY *= 0.15;
	}
	else
	{
		posX *= 0.01; // 
		posY *= 0.02; // 
		sizeX *= 0.99; // 
		sizeY *= 0.98; // 
	}

	rect.setFillColor(sf::Color(0, 0, 0, 120));
	rect.setOutlineThickness(2);
	rect.setOutlineColor(sf::Color(230, 138, 0, 255));
	rect.setPosition(posX, posY);
	rect.setSize(sf::Vector2f(sizeX, sizeY));

	text.setFont(f);
	text.setString(str);
	text.setCharacterSize(14);
	text.setPosition(posX + 5, posY + 5);

	auto viewX = larghezza/2 - posX;
	auto viewY = lunghezza/2 - posY; // Giù 0, viewY - sizeX
	auto center = sf::Vector2f(0, 0); // sizeX/2+posX, sizeY/2+posY

	view = sf::View();
	view.reset( sf::FloatRect( center , sf::Vector2f(sizeX, lunghezza) ) );
	view.setViewport( sf::FloatRect( 0, 0, 1.0f, 1.0f ) );
}


sf::Text TextBox::getText() const
{
	return this->text;
}

TextBox::~TextBox()
{
}
