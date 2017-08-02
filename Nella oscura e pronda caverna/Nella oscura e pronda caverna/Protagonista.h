#pragma once
#include "Entita.h"
class Protagonista : public Entita
{

public:
	Protagonista(std::string nome, std::vector<Oggetto> inventario, Attributi attributi, std::vector<Oggetto> equipaggiamento, unsigned int livello, double esperienza, long int fondiEconomici);
	~Protagonista();

private:
	unsigned int livello; //FIXME livello è gia contenuto dentro attributi, ereditati da Entita
	double esperienza;
	long int fondiEconomici;
};

