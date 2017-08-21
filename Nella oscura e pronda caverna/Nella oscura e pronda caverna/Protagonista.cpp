#include "Protagonista.h"
#include <memory>
Protagonista::Protagonista(std::string nome, std::list<std::shared_ptr<Oggetto>> inventario, Attributi attributi, std::vector<std::shared_ptr<Oggetto>> equipaggiamento, unsigned int livello, double esperienza, long int fondiEconomici) : Entita(nome, inventario, attributi, equipaggiamento)

{
	this->livello = livello;
	this->esperienza = esperienza;
	this->fondiEconomici = fondiEconomici;
}


Protagonista::~Protagonista()
{
}
