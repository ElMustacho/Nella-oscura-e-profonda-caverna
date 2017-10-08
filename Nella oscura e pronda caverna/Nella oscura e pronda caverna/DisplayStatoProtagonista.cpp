#include "DisplayStatoProtagonista.h"



DisplayStatoProtagonista::DisplayStatoProtagonista(Protagonista* stato)
{
	livello = stato->getLivello();
	esperienza = stato->getEsperienza();
	fondiEconomici = stato->getFondi();
	statoProtagonista = stato;
	statoProtagonista->registerObserver(this);
}

DisplayStatoProtagonista::~DisplayStatoProtagonista()
{
	if (statoProtagonista != nullptr)
	{
		statoProtagonista->removeObserver(this);
	}
	else
	{
		// Guess I'll die in peace...
	}
}

void DisplayStatoProtagonista::disconnect()
{
	if (statoProtagonista != nullptr)
	{
		statoProtagonista = nullptr;
	}
	//CHECK Maybe we can call the destrutor here
	(*this).~DisplayStatoProtagonista();
}

void DisplayStatoProtagonista::update() 
{
	if(statoProtagonista != nullptr)
	{
		livello = statoProtagonista->getLivello();
		esperienza = statoProtagonista->getEsperienza();
		fondiEconomici = statoProtagonista->getFondi();
		display();
	}
	else
	{
		// err...
	}
}

void DisplayStatoProtagonista::display() const
{
	if (statoProtagonista != nullptr)
	{
		//TODO crea finestra che visualizzi lo stato del protagonista
		std::cout << "Stato::" << std::endl;
		std::cout << "Livello: " << livello << std::endl;
		std::cout << "Esperienza: " << esperienza << std::endl;
		std::cout << "Soldi: " << fondiEconomici << std::endl;
	}
	else
	{
		// err...
	}
	
}