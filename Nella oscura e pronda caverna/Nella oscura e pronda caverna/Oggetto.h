#pragma once
#include <string>
#include "Sprite.h"

class Oggetto
{

public:
	Oggetto(double peso, std::string nome, std::string descrizione, long valore) : peso(peso), nome(nome), descrizione(descrizione), valore(valore) {}
	~Oggetto();

	virtual void usa();

	const double getPeso() 
	{
		return peso;
	}
	const std::string getNome() 
	{
		return nome;
	}
	const std::string getDescrizione() 
	{
		return descrizione;
	}
	const long getValore()
	{
		return valore;
	}

private:
	double peso;
	std::string nome, descrizione;
	long valore;
	//Sprite sprite; // TODO define and manage Sprite
};

