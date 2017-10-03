#include "DisplayStatoProtagonista.h"



DisplayStatoProtagonista::DisplayStatoProtagonista(std::shared_ptr<StatoProtagonista> stato)
{
	livello = 0;
	esperienza = 0;
	fondiEconomici = 0;
	statoProtagonista = stato;
	//statoProtagonista->registerObserver(shared_from_this()); // Before there was a simple this
} //CHECK This call generate an error (you can't call | before the contructor has called)

DisplayStatoProtagonista::~DisplayStatoProtagonista()
{
	//statoProtagonista->removeObserver(shared_from_this()); // Before there was a simple this
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