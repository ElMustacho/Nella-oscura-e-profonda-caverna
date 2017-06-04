#pragma once
#include "Entità.h"
class Protagonista : public Entità
{

public:
	Protagonista(std::string nome, Attributi attributi, unsigned int livello, double esperienza, long int fondiEconomici);
	~Protagonista();

private:
	unsigned int livello;
	double esperienza;
	long int fondiEconomici;
};

