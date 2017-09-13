#include "Arma.h"



Arma::Arma(double peso, std::string nome, std::string descrizione, long valore, Danno danno) : Oggetto(peso, nome, descrizione, valore)
{
	dannoBase = danno;
}


Arma::~Arma()
{
}

Danno Arma::getDannoBase() const {
	return dannoBase;
}

void Arma::setDannoBase(Danno danno) {
	dannoBase = danno;
}

Danno Arma::attacca()
{
	return dannoBase;
}

void Arma::Incanta(){
 	dannoBase.setParteDanno("magico", dannoBase.getParteDanno("magico") + 5);
}

void Arma::Deincanta() {

}