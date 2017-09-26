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

		rect.setFillColor(sf::Color(0, 0, 0, 120));
		rect.setOutlineThickness(2);
		rect.setOutlineColor(sf::Color(230, 138, 0, 255));
		rect.setPosition(posX, posY);
		rect.setSize(sf::Vector2f(sizeX, sizeY));

		text.setFont(f);
		text.setString(str);
		text.setCharacterSize(14);
		text.setPosition(posX + 5, posY + 5);

		//HACK prendi dim dinamicamente

		auto viewX = larghezza / 2 - posX;
		auto viewY = -lunghezza / 2 + posY;
		text.setPosition(0, 0);
		auto center = sf::Vector2f(viewX, viewY);
		auto rectSize = sf::Vector2f(sizeX, sizeY);
		rectSize = rect.getSize();

		auto rectCenter = sf::Vector2f(+380., 39);
		//auto rectCenter = sf::Vector2f(rect.getLocalBounds().left + rectSize.x/2, rect.getLocalBounds().top + rectSize.y/2);
		//center.x = 0;
		//center.y -= rect.getLocalBounds().top;
		view = sf::View(rectCenter, rectSize);
		//TODO sta schiacciando il testo
		view.setViewport(sf::FloatRect(0, 0.80f, 1.0f, 0.15f));
	}
	else
	{
		posX *= 0.01; // 
		posY *= 0.02; // 
		sizeX *= 0.99; // 
		sizeY *= 0.98; // 

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
