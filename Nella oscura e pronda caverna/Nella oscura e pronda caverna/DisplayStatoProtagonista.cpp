#include "DisplayStatoProtagonista.h"



DisplayStatoProtagonista::DisplayStatoProtagonista(StatoProtagonista* stato)
{
	livello = stato->getLivello();
	esperienza = stato->getEsperienza();
	fondiEconomici = stato->getFondi();
	statoProtagonista = stato;
	statoProtagonista->registerObserver(this);
}

DisplayStatoProtagonista::~DisplayStatoProtagonista()
{
	statoProtagonista->removeObserver(this); 
}

void DisplayStatoProtagonista::update() 
{
	livello = statoProtagonista->getLivello();
	esperienza = statoProtagonista->getEsperienza();
	fondiEconomici = statoProtagonista->getFondi();
	display();
}

void DisplayStatoProtagonista::display() const
{
	//TODO crea finestra che visualizzi lo stato del protagonista
	std::cout << "Stato::" << std::endl;
	std::cout << "Livello: " << livello << std::endl;
	std::cout << "Esperienza: " << esperienza << std::endl;
	std::cout << "Soldi: " << fondiEconomici << std::endl;
}