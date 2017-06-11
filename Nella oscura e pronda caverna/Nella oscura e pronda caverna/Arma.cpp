#include "Arma.h"



Arma::Arma(double peso, std::string nome, std::string descrizione, long valore, int danno, std::vector<bool> tipo) : Oggetto(peso, nome, descrizione, valore)
{
	this->danno = danno;
	this->tipo = tipo;
}


Arma::~Arma()
{
}

void Arma::usa()
{
	// TODO effetc!
}
