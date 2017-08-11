#include "Protagonista.h"




Protagonista::Protagonista(std::string nome, std::list<Oggetto> inventario, Attributi attributi, std::vector<Oggetto> equipaggiamento, unsigned int livello, double esperienza, long int fondiEconomici) : Entita(nome,inventario, attributi,equipaggiamento)

{
	this->livello = livello;
	this->esperienza = esperienza;
	this->fondiEconomici = fondiEconomici;
}


Protagonista::~Protagonista()
{
}
