#include "StatoProtagonista.h"


bool StatoProtagonista::registerObserver(Observer* obs)
{
	observers.push_back(obs);
	return true;
}

bool StatoProtagonista::removeObserver(Observer* obs)
{
	observers.remove(obs);
	return true;
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
	for (auto&& i : observers)
	{
		 //delete i; //TODO delete every observer (PROBLEM with Observer's destructor: inaccessibile)
	}
	observers.clear();
}
