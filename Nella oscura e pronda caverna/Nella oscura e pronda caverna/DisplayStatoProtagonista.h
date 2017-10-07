#pragma once

#include <iostream>

#include "Observer.h"
#include "Observee.h"
#include "Protagonista.h"
#include "StatoProtagonista.h"

class DisplayStatoProtagonista : public Observer
{

public:

	DisplayStatoProtagonista(StatoProtagonista* statoProtagonista);
	~DisplayStatoProtagonista();

	void update();
	void display() const;

private:
	StatoProtagonista* statoProtagonista;
	unsigned int livello;
	double esperienza;
	long int fondiEconomici;
};

