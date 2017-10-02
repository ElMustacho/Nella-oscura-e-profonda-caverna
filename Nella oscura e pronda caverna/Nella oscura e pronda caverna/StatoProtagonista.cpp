#include "StatoProtagonista.h"


bool StatoProtagonista::registerObserver(std::shared_ptr<Observer> obs)
{
	observers.push_back(obs);
	return true;
}

bool StatoProtagonista::removeObserver(std::shared_ptr<Observer> obs)
{
	observers.remove(obs);
	return true;
}

bool StatoProtagonista::notifyObservers() const
{
	for (std::list<std::shared_ptr<Observer>>::const_iterator i = observers.begin(); i != observers.end(); i++)
	{
		(*i)->update(livello, esperienza, fondiEconomici);
	}
	return (observers.size() > 0);
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
}
