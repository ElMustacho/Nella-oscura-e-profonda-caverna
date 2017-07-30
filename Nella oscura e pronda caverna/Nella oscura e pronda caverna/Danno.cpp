#include "Danno.h"



Danno::Danno(std::vector<double> partiDanno, double ammontare)
{
	tipo.insert(tipo.begin, partiDanno.begin, partiDanno.end);
	this->ammontare = ammontare;
	equalize();
}

Danno::Danno(bool noDanno) {
	
}

void Danno::equalize() 
{
	double totale = 0;
	for each(double numero in tipo) {
		totale += numero;
	}
	if (totale == 0)
		ammontare = 0;
	else {

	}
}

Danno::~Danno()
{
}
