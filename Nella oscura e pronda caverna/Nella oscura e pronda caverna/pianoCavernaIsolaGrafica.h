#pragma once
#include "pianoCavernaIsola.h"
#include "SFML\Graphics.hpp"
#include "TextBox.h"

class pianoCavernaIsolaGrafica :
	public pianoCavernaIsola
{
public:
	int playPiano();
	int playerAct(bool loquace, sf::RenderWindow &window, std::vector<Casella> pavimento, int larghezza, int lunghezza, sf::Sprite tiles, sf::Sprite ogg, sf::Sprite prot, sf::Sprite enem, TextBox& messages);
	pianoCavernaIsolaGrafica(int larghezza, int lunghezza);
	void stampaPianoSuFinestra();
	~pianoCavernaIsolaGrafica();
};

