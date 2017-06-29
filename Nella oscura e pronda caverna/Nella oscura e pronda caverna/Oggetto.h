#pragma once
#include <string>
#include "Sprite.h"

class Oggetto
{

public:
	Oggetto(double peso, std::string nome, std::string descrizione, long valore) : peso(peso), nome(nome), descrizione(descrizione), valore(valore) {}
	~Oggetto();

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
	Sprite sprite; // TODO define and manage Sprite
};

