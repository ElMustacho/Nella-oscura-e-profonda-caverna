#pragma once
#include "Entita.h"

class Protagonista : public Entita
{

public:
	Protagonista(std::string nome, Attributi attributi, unsigned int livello, double esperienza, long int fondiEconomici);
	~Protagonista();

private:
	unsigned int livello;
	double esperienza;
	long int fondiEconomici;
};

