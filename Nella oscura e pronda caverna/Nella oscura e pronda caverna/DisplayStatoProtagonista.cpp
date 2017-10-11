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
		//TODO A causa dell'HACK non è possibile fare i controlli correttamente
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
		
		sf::String msg("Stato di " + nome + "::\n");
		msg += "HP: " + std::to_string(hp) + "\n";
		msg += "Livello: " + std::to_string(livello) + "\n";
		msg += "Esperienza: " + std::to_string(esperienza) + "\n";
		msg += "Soldi: " + std::to_string(fondiEconomici) + "\n";

		std::cout << msg.toAnsiString() << std::endl;
		popUp(msg); // Spunta fuori prima del refresh mostrando il futuro
	}
	else
	{
		// err...
	}
	
}

void DisplayStatoProtagonista::displayHp() const
{
	if (statoProtagonista != nullptr)
	{
		//TODO crea finestra che visualizzi lgli hp del protagonista
		sf::String msg("HP di " + nome + ": " + std::to_string(hp) + "\n");

		std::cout << msg.toAnsiString() << std::endl;
		popUp(msg); // Spunta fuori prima del refresh mostrando il futuro
	}
	else
	{
		// err...
	}
}