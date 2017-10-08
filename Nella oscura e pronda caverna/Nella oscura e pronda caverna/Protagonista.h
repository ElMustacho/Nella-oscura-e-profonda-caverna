#pragma once
#include "Entita.h"
#include "Observee.h"

class Protagonista : public Entita, public Observee
{

public:
	Protagonista(std::string nome, std::vector<std::shared_ptr<Oggetto>> inventario, Attributi attributi, Equipaggiamento equipaggiamento, unsigned int livello, double esperienza, long int fondiEconomici, std::string posToFile="");
	
	virtual ~Protagonista();
	
	virtual void onDeath(TextBox& messages) override;

	bool registerObserver(Observer* obs);
	bool removeObserver(Observer* obs);
	bool notifyObservers() const;
	int numObservers() const;

	void statoCambiato();

	unsigned int getLivello() const
	{
		return livello;
	}

	void setLivello(double livello)
	{
		this->livello = livello;
		statoCambiato();
	};

	double getEsperienza() const
	{
		return esperienza;
	}

	void setEsperienza(double esperienza) 
	{
		this->esperienza = esperienza; 
		statoCambiato(); 
	};

	long int getFondi() const
	{
		return fondiEconomici;
	}

	void setFondi(long int fondi)
	{
		this->fondiEconomici = fondi;
		statoCambiato();
	}

private:
	std::list<Observer*> observers;
	unsigned int livello; //FIXME livello è gia contenuto dentro attributi, ereditati da Entita
	double esperienza;
	long int fondiEconomici;
};

