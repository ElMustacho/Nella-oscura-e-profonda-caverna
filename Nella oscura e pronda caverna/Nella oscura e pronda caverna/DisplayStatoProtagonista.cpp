#include "DisplayStatoProtagonista.h"
#include "UtilityGrafica.h"



DisplayStatoProtagonista::DisplayStatoProtagonista(Entita* stato)
{
	auto statoC = dynamic_cast<Protagonista*> (stato);
	if (statoC != nullptr)
	{
		nome = statoC->getNome();
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
		auto lv = statoProtagonista->getLivello();
		if (livello != lv)
		{
			livello = lv;
			//displayLv();
		}

		auto esp = statoProtagonista->getEsperienza();
		if (esperienza!= esp)
		{
			esperienza = esp;
			//displayEsp();
		}

		auto money = statoProtagonista->getFondi();
		if (fondiEconomici = money)
		{
			fondiEconomici = money;
			//displayEco();
		}
		
		auto health = statoProtagonista->getHp();
		if (hp != health)
		{
			hp = health;
			//displayHp();
		}
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
		std::cout << "Stato " << nome << "::"<<std::endl;
		std::cout << "HP: " << hp << std::endl;
		std::cout << "Livello: " << livello << std::endl;
		std::cout << "Esperienza: " << esperienza << std::endl;
		std::cout << "Soldi: " << fondiEconomici << std::endl;

		sf::String msg("Stato " + nome + "::\n");
		msg += "HP: " + std::to_string(hp) + "\n";
		msg += "Livello: " + std::to_string(livello) + "\n";
		msg += "Esperienza: " + std::to_string(esperienza) + "\n";
		msg += "Soldi: " + std::to_string(fondiEconomici) + "\n";
		popUp(msg);
	}
	else
	{
		// err...
	}
	
}