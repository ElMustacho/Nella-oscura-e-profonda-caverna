#pragma once

#include <iostream>

#include "Observer.h"
#include "Observee.h"
#include "Protagonista.h"

class DisplayStatoProtagonista : public Observer , std::enable_shared_from_this <DisplayStatoProtagonista>
{

public:

	DisplayStatoProtagonista(std::shared_ptr<Observee> statoProtagonista);
	~DisplayStatoProtagonista();

	void update(unsigned int lv, double exp, long int money);
	void display() const;

	void regist();

private:
	std::shared_ptr<Observee> statoProtagonista;
	unsigned int livello;
	double esperienza;
	long int fondiEconomici;
};

