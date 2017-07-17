#pragma once
#include <vector>
#include "Casella.h"
#include "Entita.h"
#include "Oggetto.h"
#include "Protagonista.h"
#include "Attore.h"

class Piano
{
public:
	~Piano();
	int posizione(int x, int y);
	Casella& at(int x, int y) 
	{ 
		return pavimento.at(x + y * lunghezza);// LOOKATME sbagliato può restituire valori non accettabili --> corretto in un altro ramo
	} 
	bool GeneratoreV1();
	bool creaStanzaRettangolare(int posX, int posY, int dimX, int dimY);
	bool creaPorte(int posX, int posY, int dimX, int dimY);
	void StampaChar();
	int muoviEntita(int posX, int posY, int targetX, int targetY);
	void StampaFileChar();
	bool popolaPiano();
	bool spargiLoot();
	//TODO insert Djikstra
	Piano(int larghezza, int lunghezza, int sceltaGeneratore, std::vector<Oggetto> lootPossibile, std::vector<Entita> entitàPossibili);
private:
	std::vector<Casella> pavimento;
	int sceltaGeneratore, lunghezza, larghezza; //per ora considererò solo il caso a stanze regolari, non con perlin noise
	std::vector<Entita> entitaGenerabili;
	std::vector<Oggetto> oggettiGenerabili;
};
