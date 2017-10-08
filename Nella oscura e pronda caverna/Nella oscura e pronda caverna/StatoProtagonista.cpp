#include "StatoProtagonista.h"


bool StatoProtagonista::registerObserver(Observer* obs)
{
	observers.push_back(obs);
	return true;
}

bool StatoProtagonista::removeObserver(Observer* obs)
{
	if (observers.size() > 0 && obs != nullptr)
	{
		observers.remove(obs);
		obs->disconnect();
		return true;
	}
	return false;
}

bool StatoProtagonista::notifyObservers() const
{
	for (auto i = observers.begin(); i != observers.end(); i++)
	{
		(*i)->update();
	}
	return (observers.size() > 0);
}

int StatoProtagonista::numObservers() const
{
	return observers.size();
}

void StatoProtagonista::statoCambiato()
{ 
	notifyObservers(); 
}

void StatoProtagonista::setStato(unsigned int lv, double exp, long int money)
{
	livello = lv;
	esperienza = exp;
	fondiEconomici = money;
	statoCambiato();
}

StatoProtagonista::~StatoProtagonista()
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
