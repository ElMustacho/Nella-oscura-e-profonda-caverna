#include "Protagonista.h"
#include "DisplayStatoProtagonista.h"

#include <memory>
#include <iostream>


Protagonista::Protagonista(std::string nome, std::vector<std::shared_ptr<Oggetto>> inventario, Attributi attributi, Equipaggiamento equipaggiamento, unsigned int livello, double esperienza, long int fondiEconomici, std::string posTofile) : Entita(nome, inventario, attributi, equipaggiamento, posTofile)

{
	this->livello = livello;
	this->esperienza = esperienza;
	this->fondiEconomici = fondiEconomici;
}


Protagonista::~Protagonista()
{
	if (observers.size() > 0)
	{
		for (auto i = observers.begin(); i != observers.end(); i++)
		{
			(*i)->disconnect();
			//observers.remove(*i); // IF the part above work this is not necessary
		}
		observers.clear(); // Same
	}
}


bool Protagonista::registerObserver(Observer* obs)
{
	observers.push_back(obs);
	return true;
}

bool Protagonista::removeObserver(Observer* obs)
{
	if (observers.size() > 0 && obs != nullptr)
	{
		observers.remove(obs);
		obs->disconnect();
		return true;
	}
	return false;
}

bool Protagonista::notifyObservers() const
{
	for (auto i = observers.begin(); i != observers.end(); i++)
	{
		(*i)->update();
	}
	return (observers.size() > 0);
}

int Protagonista::numObservers() const
{
	return observers.size();
}

void Protagonista::statoCambiato()
{
	DisplayStatoProtagonista dispStat(this); //HACK trovare il modo giusto di registrarci un observe
	notifyObservers();
}

void Protagonista::onDeath(TextBox& messages)
{
	/*std::cout << "Sei orribilmente morto." << std::endl;
	messages.text.setString("Sei orribilmente morto.\n");
	char a;
	std::cin >> a;
	exit(EXIT_SUCCESS);*/
}
