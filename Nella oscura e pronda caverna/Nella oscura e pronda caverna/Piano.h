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
	bool removeEntita(cood coodElimina);
	void scontro(cood posizioneVittima, cood posizioneAttaccante);
	void scontro(cood posizioneVittima, Danno dannoInflitto); //gestisce danno ad area e fulmini da divinità furiose
	Casella& at(int x, int y);
	Casella& at(cood coord);
	bool isCoodLegal(cood coord);
	int posizione(cood coord);
	cood fromPosizioneToInt(int x);
	bool creaStanzaRettangolare(int posX, int posY, int dimX, int dimY); 
	bool creaPorte(int posX, int posY, int dimX, int dimY);
	std::vector<std::shared_ptr<Entita>> getVectorEntita();
	std::vector<cood> getVectorPosizioni();
	std::vector<cood> floodFill (cood posizionePartenza);
	void StampaChar();
	int muoviEntita(int posX, int posY, int targetX, int targetY); 
	void StampaFileChar();
	bool popolaPiano();
	bool spargiLoot();
	bool placeEntita(std::shared_ptr<Entita> placeMe, cood coord);
	Piano();
	Piano(int larghezza, int lunghezza, std::vector<std::shared_ptr<Oggetto>> lootPossibile, std::vector<std::shared_ptr<Entita>> entitaPossibili);
	std::shared_ptr<Entita> entityFactory(std::string nome);
	std::shared_ptr<Entita> entityFactory(int codiceID=0);
	//Piano(std::string posizione, bool &successo); //Da file 
protected:
	std::vector<Casella> pavimento; 
	int lunghezza, larghezza; 
	std::vector<std::shared_ptr<Entita>> entitaGenerabili;
	std::vector<std::shared_ptr<Oggetto>> oggettiGenerabili;
	std::vector<std::pair<std::shared_ptr<Entita>, cood>> entitaPresenti;
};
