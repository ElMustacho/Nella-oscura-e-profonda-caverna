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
		std::list<Oggetto> presi; // FIXME change it
		return presi; 
	}
}