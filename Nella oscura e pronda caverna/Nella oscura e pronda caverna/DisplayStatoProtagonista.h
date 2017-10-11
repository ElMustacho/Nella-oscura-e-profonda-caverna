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

	DisplayStatoProtagonista(Entita* statoProtagonista);
	virtual ~DisplayStatoProtagonista();

	void update();
	void display() const;
	void disconnect();

private:
	Protagonista* statoProtagonista;
	unsigned int livello;
	double esperienza;
	long int fondiEconomici;
};

