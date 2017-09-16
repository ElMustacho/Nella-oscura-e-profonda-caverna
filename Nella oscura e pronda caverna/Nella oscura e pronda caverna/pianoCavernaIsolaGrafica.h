#pragma once
#include "pianoCavernaIsola.h"
#include "SFML\Graphics.hpp"

class pianoCavernaIsolaGrafica :
	public pianoCavernaIsola
{
public:
	int playPiano();
	int playerAct(bool loquace, sf::Window &window);
	pianoCavernaIsolaGrafica(int larghezza, int lunghezza, std::string posizioneFile="");
	void stampaPianoSuFinestra();
	~pianoCavernaIsolaGrafica();
private:
	std::string posizioneFile;
	sf::Texture texturePavimento;
};

