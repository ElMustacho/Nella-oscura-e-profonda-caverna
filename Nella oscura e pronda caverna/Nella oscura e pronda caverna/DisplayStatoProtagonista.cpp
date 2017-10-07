#include "DisplayStatoProtagonista.h"



DisplayStatoProtagonista::DisplayStatoProtagonista(StatoProtagonista* stato)
{
	livello = stato->getLivello();
	esperienza = stato->getEsperienza();
	fondiEconomici = stato->getFondi();
	statoProtagonista = stato;
	statoProtagonista->registerObserver(this); // Before there was a simple this
} //CHECK This call generate an error (you can't call | before the contructor has called)

DisplayStatoProtagonista::~DisplayStatoProtagonista()
{
	statoProtagonista->removeObserver(this); // Before there was a simple this
}

void DisplayStatoProtagonista::update() //unsigned int lv, double exp, long int money
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