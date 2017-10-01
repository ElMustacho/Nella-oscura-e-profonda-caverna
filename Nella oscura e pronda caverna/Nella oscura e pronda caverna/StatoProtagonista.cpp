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
	for (std::list<Observer*>::const_iterator i = observers.begin(); i != observers.end(); i++)
	{
		(*i)->update(livello, esperienza, fondiEconomici, nome, attributi, inventario, equipaggiamento);
	}
	return (observers.size() > 0);
}

void StatoProtagonista::statoCambiato()
{ 
	notifyObservers(); 
}

void StatoProtagonista::setStato(unsigned int lv, double exp, long int money, std::string name, Attributi attr, std::vector<std::shared_ptr<Oggetto>> inventory, Equipaggiamento equip)
{
	livello = lv;
	esperienza = exp;
	fondiEconomici = money;
	nome = name;
	attributi = attr;
	inventario = inventory;
	equipaggiamento = equip;
	statoCambiato();
}

StatoProtagonista::~StatoProtagonista()
{
}
