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
	void windowRefresh(sf::RenderWindow& window, std::vector<Casella> pavimento, int larghezza, int lunghezza, TextBox messages);
	void windowRefresh2(sf::RenderWindow& window, TextBox mesagges);
	void windowMessageRefresh(sf::RenderWindow& window, TextBox messages);
	void popUp(sf::String);
	sf::String graphicInput2(sf::String text);
	sf::String graphicInput(sf::RenderWindow& window, TextBox& messages);
	void update(double a, double b, double c);
	void updateLevel(int livello);
	UtilityGrafica(sf::Sprite tiles = sf::Sprite(), sf::Sprite ogg = sf::Sprite(), sf::Sprite prot = sf::Sprite(), sf::Sprite enem = sf::Sprite(), sf::Sprite scale = sf::Sprite());
	~UtilityGrafica();
	
private:
	sf::Sprite tiles, ogg, prot, enem, scale;
	double percHP, percSt, percMa;
	int livelloPG;

};