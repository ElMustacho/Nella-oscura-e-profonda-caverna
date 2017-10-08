#pragma once

#include <iostream>

#include "Observer.h"
#include "Observee.h"
#include "Protagonista.h"
#include "StatoProtagonista.h"
#include "DisplayElement.h"

class DisplayStatoProtagonista : public Observer, public DisplayElement
{

public:

	DisplayStatoProtagonista(StatoProtagonista* statoProtagonista);
	virtual ~DisplayStatoProtagonista();

	void update();
	void display() const;
	void disconnect();

private:
	StatoProtagonista* statoProtagonista;
	unsigned int livello;
	double esperienza;
	long int fondiEconomici;
};

