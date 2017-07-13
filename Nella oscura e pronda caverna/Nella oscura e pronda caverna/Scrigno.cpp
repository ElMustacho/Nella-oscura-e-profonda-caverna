#include "Scrigno.h"



Scrigno::Scrigno(double peso, std::string nome, std::string descrizione, long valore, int unlock, std::list<Oggetto> loot) : Oggetto( peso, nome, descrizione, valore)
{
	this->loot = loot;
	this->unlock = unlock;
}


Scrigno::~Scrigno()
{
}


std::list<Oggetto> Scrigno::prendiOggetto(Oggetto* scelta) // TODO finish this
{
	if (scelta == nullptr)
	{
		return loot;
	}
	else
	{
		std::list<Oggetto> presi; // CHECK Is it ok?

		std::list<Oggetto>::iterator it = loot.begin;
		while ( (*it).getNome() != scelta->getNome() && it != loot.end)
		{
			it++;
		}
		if (it != loot.end)
		{
			presi.push_back(*it);
			loot.erase(it);
		}

		return presi;
	}
}

void Scrigno::inserisciOggetto(Oggetto* obj)
{
	this->loot.push_back(*obj); //CHECK not sure, I'll be back
}