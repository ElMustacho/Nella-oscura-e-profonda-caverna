#pragma once

#include <iostream>

#include "sfml\Graphics.hpp"
#include "TextBox.h"
#include "Casella.h"
#include "Attore.h"
#include "Observer.h"


class UtilityGrafica : public Observer
{
public:
	void windowRefresh(std::vector<Casella> pavimento);
	void windowRefresh2(sf::RenderWindow& window, TextBox mesagges);
	void windowMessageRefresh(TextBox messages);
	void popUp(sf::String);
	sf::String graphicInput2(sf::String text);
	sf::String graphicInput(sf::RenderWindow& window, TextBox& messages);
	void update(double a, double b, double c);
	void updateLevel(int livello);
	UtilityGrafica(int lung, int larg, sf::Sprite tiles, sf::Sprite ogg, sf::Sprite prot, sf::Sprite enem, sf::Sprite scale);
	UtilityGrafica();
	~UtilityGrafica();
	

	//TODO Adjust
	sf::RenderWindow& getWindow()
	{
		return window;
	}

	//TODO Adjust
	TextBox& getTextBox()
	{
		return messages;
	}

private:
	sf::RenderWindow window;
	sf::Font font;
	TextBox messages;
	int lunghezza, larghezza;
	sf::Sprite tiles, ogg, prot, enem, scale;
	double percHP, percSt, percMa;
	int livelloPG;

};