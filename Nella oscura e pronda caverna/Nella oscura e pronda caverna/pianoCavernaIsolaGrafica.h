#pragma once
#include "pianoCavernaIsola.h"
#include "SFML\Graphics.hpp"
#include "TextBox.h"
#include "UtilityGrafica.h"

class pianoCavernaIsolaGrafica :
	public pianoCavernaIsola
{
public:

	int playPiano();
	//int playerAct(bool loquace, sf::Window &window);
	pianoCavernaIsolaGrafica(int larghezza, int lunghezza, std::string posizioneFile = "", std::vector<std::shared_ptr<Oggetto>> oggettiPossibili = {}, std::shared_ptr<Entita> player=nullptr, std::vector<std::shared_ptr<Entita>> entitaGenerabili = {});

	
	//int playPiano();
	int playerAct(sf::RenderWindow &window, TextBox& messages, UtilityGrafica& finestra);
	//pianoCavernaIsolaGrafica(int larghezza, int lunghezza);

	~pianoCavernaIsolaGrafica();
private:
	std::string posizioneFile;
	sf::Texture texturePavimento;
};

