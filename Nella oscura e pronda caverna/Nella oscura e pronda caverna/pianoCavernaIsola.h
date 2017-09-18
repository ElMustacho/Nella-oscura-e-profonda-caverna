#pragma once
#include "Piano.h"
class pianoCavernaIsola :
	public Piano
{
public:
	pianoCavernaIsola(int larghezza, int lunghezza, std::vector<std::shared_ptr<Oggetto>> oggettiPossibili = {}); //Prende la dimensione del piano, restituisce la posizione del personaggio
	~pianoCavernaIsola();
	bool rSpargiLoot(std::vector<cood> posizioniValide);
};

