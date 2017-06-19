#include "Protagonista.h"



Protagonista::Protagonista(std::string nome, Attributi attributi, unsigned int livello, double esperienza, long int fondiEconomici) : Entita(nome, attributi)
{
	this->livello = livello;
	this->esperienza = esperienza;
	this->fondiEconomici = fondiEconomici;
}


Protagonista::~Protagonista()
{
}
