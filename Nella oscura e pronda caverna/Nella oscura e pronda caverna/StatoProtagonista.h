#pragma once

#include "Protagonista.h"
#include "Observee.h"

class StatoProtagonista : public Observee
{

public:
	StatoProtagonista() : livello(0), esperienza(0), fondiEconomici(0) {}
	~StatoProtagonista();

	bool registerObserver(Observer* obs);
	bool removeObserver(Observer* obs);
	bool notifyObservers() const;

	void statoCambiato();
	void setStato(unsigned int lv, double exp, long int money);
	int numObservers() const;
	
	unsigned int getLivello() const
	{
		return livello;
	}

	double getEsperienza() const
	{
		return esperienza;
	}

	long int getFondi() const
	{
		return fondiEconomici;
	}

private:
	std::list<Observer*> observers;
	unsigned int livello;
	double esperienza;
	long int fondiEconomici;
};

