#pragma once
#include <vector>
#include "Casella.h"
#include "Entita.h"
#include "Oggetto.h"
#include "Protagonista.h"
#include "Attore.h"
/*
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
	~Piano();
	int posizione(int x, int y);
	Casella& at(int x, int y); 
	bool GeneratoreV1();
	bool creaStanzaRettangolare(int posX, int posY, int dimX, int dimY);
	bool creaPorte(int posX, int posY, int dimX, int dimY);
	void StampaChar();
	int muoviEntita(int posX, int posY, int targetX, int targetY); //CHECK faccio cose strane, ma forse è Piano (std::string posizione, bool &successo);
	void StampaFileChar();
	bool popolaPiano();
	bool spargiLoot();
	Piano(int larghezza, int lunghezza, int sceltaGeneratore, std::vector<Oggetto> lootPossibile, std::vector<Entita> entitàPossibili);
	Piano(std::string posizione, bool &successo); //CHECK faccio cose strane, ma forse è int muoviEntita(int posX, int posY, int targetX, int targetY);
private:
	std::vector<Casella> pavimento; 
	int sceltaGeneratore, lunghezza, larghezza; //per ora considererò solo il caso a stanze regolari, non con perlin noise
	std::vector<Entita> entitaGenerabili;
	std::vector<Oggetto> oggettiGenerabili;
};

