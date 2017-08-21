#pragma once
#include "Piano.h"
class pianoCavernaIsola :
	public Piano
{
public:
	pianoCavernaIsola(int larghezza, int lunghezza); //Prende la dimensione del piano, restituisce la posizione del personaggio
	~pianoCavernaIsola();
	bool spargiLoot(std::vector<cood> posizioniValide);
};

