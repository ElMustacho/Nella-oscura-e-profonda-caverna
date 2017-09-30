#pragma once

#include "Observer.h"
#include "Observee.h"
#include "Protagonista.h"

class DisplayStatoProtagonista : public Observer
{

public:

	DisplayStatoProtagonista(Observee& statoProtagonista);
	~DisplayStatoProtagonista();

	void update(unsigned int lv, double exp, long int money, std::string name, Attributi attr, std::vector<std::shared_ptr<Oggetto>> inventory, Equipaggiamento equip);
	void display() const;

private:
	Observee& statoProtagonista;
	unsigned int livello;
	double esperienza;
	long int fondiEconomici;
	std::string nome;
	Attributi attributi;
	std::vector<std::shared_ptr<Oggetto>> inventario;
	Equipaggiamento equipaggiamento;
};

