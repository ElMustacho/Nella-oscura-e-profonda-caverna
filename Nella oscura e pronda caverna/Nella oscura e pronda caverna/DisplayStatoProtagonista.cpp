#include "DisplayStatoProtagonista.h"



DisplayStatoProtagonista::DisplayStatoProtagonista(Entita* stato)
{
	auto statoC = dynamic_cast<Protagonista*> (stato);
	if (statoC != nullptr)
	{
		livello = statoC->getLivello();
		hp = statoC->getHp();
		esperienza = statoC->getEsperienza();
		fondiEconomici = statoC->getFondi();
		statoProtagonista = statoC;
		statoProtagonista->registerObserver(this);
	}
	else
	{
		// err...
	}
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
		hp = statoProtagonista->getHp();
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
		std::cout << "HP: " << hp << std::endl;
		std::cout << "Livello: " << livello << std::endl;
		std::cout << "Esperienza: " << esperienza << std::endl;
		std::cout << "Soldi: " << fondiEconomici << std::endl;
	}
	else
	{
		// err...
	}
	
}