#pragma once
#include <string>
#include "Sprite.h"
#include "Danno.h"
class Oggetto
{

public:
	Oggetto(double peso, std::string nome, std::string descrizione, long valore) : peso(peso), nome(nome), descrizione(descrizione), valore(valore) {}
	~Oggetto();
	//Tutto può essere un'arma se sei abbastanza disperato e/o creativo
	Danno attacca();
	bool operator==(const Oggetto rOggetto) const;
	bool operator!=(const Oggetto rOggetto) const { return !operator==(rOggetto); };
	virtual void usa();

	double getPeso() const
	{
		return peso;
	}
	std::string getNome() const
	{
		return nome;
	}
	std::string getDescrizione() const
	{
		return descrizione;
	}
	long getValore() const
	{
		return valore;
	}

private:
	double peso;
	std::string nome, descrizione;
	long valore;
	//Sprite sprite; // TODO define and manage Sprite
};

