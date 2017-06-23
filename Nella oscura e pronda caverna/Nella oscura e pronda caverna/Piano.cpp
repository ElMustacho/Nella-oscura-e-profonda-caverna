#include <iostream>
#include "Piano.h"


Piano::~Piano()
{
}

int Piano::posizione(int x, int y) {
	return x + y*lunghezza;
}

bool Piano::popolaPiano()
{
	return false;
}

bool Piano::spargiLoot() 
{
	return false;
}

Piano::Piano(int larghezza, int lunghezza, int sceltaGeneratore, std::vector<Oggetto> lootPossibile, std::vector<Entita> entitàPossibili)
{
	this->lunghezza = lunghezza;
	this->larghezza = larghezza;
	pavimento.reserve(lunghezza*larghezza); //Velocizza l'accesso futuro alla memoria.
	pavimento = std::vector<Casella>(lunghezza*larghezza, Casella()); //Riempio tutto di muri all'inizio
	
	switch (sceltaGeneratore)
	{
	case 1:
		if (1==1)//TODO controlli sulla validità del piano.
		auto generato = GeneratoreV1();
	default:
		break;
		auto generato = GeneratoreV1();//questo sarà il generatore di default.
	}
}

bool Piano::GeneratoreV1() {
	return false;
}

bool Piano::creaStanzaRettangolare(int posX, int posY, int dimX, int dimY) {
	if (posX + dimX - 1 > lunghezza || posY + dimY - 1 > larghezza)
		return false; //Stanza prodotta fuori dal piano
	
	for (int i = posX; i < dimX + posX; i++) {
		for (int j = posY; j < dimY + posY; j++)
			if (!pavimento.at(posizione(i,j)).isMuro()) {
				return false; //Spazio per stanza non trovato
			}
	}
	for (int i = posX; i < dimX + posX; i++) {
		for (int j = posY; j < dimY + posY; j++)
			{
				pavimento.at(posizione(i, j)).Scava(); //Crea stanza
			}
	}
	return true;
}

void Piano::StampaChar() {
	for (int i = 0; i < lunghezza*larghezza; i++)
	{
		if (pavimento.at(i).isMuro())
			std::cout << '#';
		else
			std::cout << '.';
		if ((i+1)%lunghezza == 0)
			std::cout << std::endl;
	}
}


