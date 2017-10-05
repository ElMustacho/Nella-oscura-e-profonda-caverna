#pragma once

#include <iostream>

#include "Observer.h"
#include "Observee.h"
#include "Protagonista.h"
#include "StatoProtagonista.h"

class DisplayStatoProtagonista : public Observer , std::enable_shared_from_this <DisplayStatoProtagonista>
{

public:

	DisplayStatoProtagonista(std::shared_ptr<StatoProtagonista> statoProtagonista);
	~DisplayStatoProtagonista();

	void update();
	void display() const;

private:
	std::shared_ptr<StatoProtagonista> statoProtagonista;
	unsigned int livello;
	double esperienza;
	long int fondiEconomici;
};

