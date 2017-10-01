#pragma once

#include "Protagonista.h"
#include "Observee.h"

class StatoProtagonista : public Observee
{

public:
	StatoProtagonista() : livello(0), esperienza(0), fondiEconomici(0), nome(""), attributi(), inventario(), equipaggiamento()
	{

	}

	~StatoProtagonista();

	bool registerObserver(Observer* obs);
	bool removeObserver(Observer* obs);
	bool notifyObservers() const;

	void statoCambiato();

	void setStato(unsigned int lv, double exp, long int money, std::string name, Attributi attr, std::vector<std::shared_ptr<Oggetto>> inventory, Equipaggiamento equip);
	
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

	std::string getNome() const
	{
		return nome;
	}

	Attributi getAttributi() const
	{
		return attributi;
	}

	std::vector<std::shared_ptr<Oggetto>> getInventario() const
	{
		return inventario;
	}

	Equipaggiamento getEquipagiamento() const
	{
		return equipaggiamento;
	}

private:
	std::list<Observer*> observers;
	unsigned int livello; //FIXME livello è gia contenuto dentro attributi, ereditati da Entita
	double esperienza;
	long int fondiEconomici;
	std::string nome;
	Attributi attributi;
	std::vector<std::shared_ptr<Oggetto>> inventario;
	Equipaggiamento equipaggiamento;
};

