#pragma once
#include <vector>
#include "Casella.h"
#include "Entita.h"
#include "Oggetto.h"
#include "Protagonista.h"
#include "Attore.h"
typedef std::pair<int, int> cood;
/*
LOOKATME
Che sia chiaro una volta per tutte, anche perché io mi sbaglio più o meno sempre, dannato sia il 2D
 
	l larghezza ---> X
	u ##################
	n ##################
	g ########........##
	h ########........##
	e ########........##
	z #############.####
	z #############.####
	a #############.####
	| #############.####
	| ###..............#
	| ###..............#
	V ###..............#
	  ###..............#
	Y ##################
*/
class Piano
{
public:
	virtual ~Piano();
	
	int posizione(int x, int y);

	Casella& at(int x, int y);
	Casella& at(cood coord);
	bool isCoodLegal(cood coord);
	int posizione(cood coord);
	cood fromPosizioneToInt(int x);
	bool creaStanzaRettangolare(int posX, int posY, int dimX, int dimY); 
	bool creaPorte(int posX, int posY, int dimX, int dimY);
	std::vector<Entita*> getVectorEntita();
	std::vector<cood> getVectorPosizioni();
	std::vector<cood> floodFill (cood posizionePartenza);
	void StampaChar();
	int muoviEntita(int posX, int posY, int targetX, int targetY); 
	void StampaFileChar();
	bool popolaPiano();
	bool spargiLoot();
	bool placeEntita(Entita* placeMe, cood coord);
	Piano();
	Piano(int larghezza, int lunghezza, std::vector<Oggetto*> lootPossibile, std::vector<Entita> entitaPossibili);
	Entita* entityFactory(std::string nome);
	Entita* entityFactory(int codiceID=0);
	//Piano(std::string posizione, bool &successo); //Da file 
protected:
	std::vector<Casella> pavimento; 
	int lunghezza, larghezza; 
	std::vector<Entita> entitaGenerabili;
	std::vector<Oggetto*> oggettiGenerabili;
	std::vector<std::pair<Entita*, cood>> entitaPresenti;
};
