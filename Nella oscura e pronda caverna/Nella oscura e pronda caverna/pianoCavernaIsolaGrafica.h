#pragma once
#include "pianoCavernaIsola.h"
#include "SFML\Graphics.hpp"
#include "TextBox.h"

class pianoCavernaIsolaGrafica :
	public pianoCavernaIsola
{
public:
	int playPiano();
	int playerAct(bool loquace, sf::RenderWindow &window, TextBox& messages);
	pianoCavernaIsolaGrafica(int larghezza, int lunghezza);
	void stampaPianoSuFinestra();
	~pianoCavernaIsolaGrafica();
};

