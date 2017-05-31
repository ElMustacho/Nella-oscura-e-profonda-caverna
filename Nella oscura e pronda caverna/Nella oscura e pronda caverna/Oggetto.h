#pragma once
#include <string>
class Oggetto
{

public: // CHECK Why this? Implement it in cpp file we should
	Oggetto(double peso, std::string nome, std::string descrizione, long valore) : peso(peso), nome(nome), descrizione(descrizione), valore(valore) {}
	~Oggetto();

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
	Sprite sprite; // TODO define Sprite
};

