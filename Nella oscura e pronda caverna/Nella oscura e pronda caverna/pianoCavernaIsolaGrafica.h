#pragma once
#include "pianoCavernaIsola.h"
#include "SFML\Graphics.hpp"

class pianoCavernaIsolaGrafica :
	public pianoCavernaIsola
{
public:
	int playPiano();
	int playerAct(bool loquace, sf::Window &window);
	pianoCavernaIsolaGrafica(int larghezza, int lunghezza);
	void stampaPianoSuFinestra();
	~pianoCavernaIsolaGrafica();
};

