#pragma once
#include "Entit�.h"
class Protagonista : public Entit�
{

public:
	Protagonista(std::string nome, Attributi attributi, unsigned int livello, double esperienza, long int fondiEconomici);
	~Protagonista();

private:
	unsigned int livello;
	double esperienza;
	long int fondiEconomici;
};

