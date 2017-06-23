#pragma once
#include <vector>
#include "Casella.h"
#include "Entita.h"
#include "Oggetto.h"
class Piano
{
public:
	~Piano();
	int posizione(int x, int y);
	const Casella& at(int x, int y) const { return pavimento.at(y + x * lunghezza); }
	Casella& at(int x, int y) { return pavimento.at(y + x * lunghezza); }
	bool GeneratoreV1();
	bool creaStanzaRettangolare(int posX, int posY, int dimX, int dimY);
	void StampaChar();
	bool popolaPiano();
	bool spargiLoot();
	Piano(int larghezza, int lunghezza, int sceltaGeneratore, std::vector<Oggetto> lootPossibile, std::vector<Entita> entit�Possibili);
private:
	std::vector<Casella> pavimento;
	int sceltaGeneratore, lunghezza, larghezza; //per ora considerer� solo il caso a stanze regolari, non con perlin noise
	std::vector<Entita> entitaGenerabili;
	std::vector<Oggetto> oggettiGenerabili;
};
