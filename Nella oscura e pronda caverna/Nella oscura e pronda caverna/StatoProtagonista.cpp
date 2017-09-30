#include "StatoProtagonista.h"



StatoProtagonista::StatoProtagonista()
{
}

bool StatoProtagonista::registerObserver(Observer& obs)
{
	std::vector<Observer&>::iterator temp = find(observers.begin(), observers.end(), obs);
	if (temp != observers.end())
		return false;

	observers.push_back(obs);
	return true;
}

bool StatoProtagonista::removeObserver(Observer& obs)
{
	std::vector<Observer&>::iterator temp = find(observers.begin(), observers.end(), obs);
	if (temp == observers.end())
		return false;
	else
		observers.erase(temp);
	return true;
}

bool StatoProtagonista::notifyObservers() const
{
	for (std::vector<Observer&>::const_iterator i = observers.begin(); i != observers.end(); i++)
	{
		i->update(/*something*/);
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
