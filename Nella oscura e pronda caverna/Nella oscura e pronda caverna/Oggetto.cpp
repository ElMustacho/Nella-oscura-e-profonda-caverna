#include "Oggetto.h"
#include <cmath>
Oggetto::~Oggetto()
{
}

Danno Oggetto::attacca() {
	std::vector<double> tmp;
	for (int i = 0; i < 3; i++)
		tmp.push_back((double)1/(double)3);	//Un oggetto non inteso come arma fa danni equamente taglienti, contundenti e perforanti
	return Danno(tmp,1 + log(peso)); // a meno che il peso non sia negativo il danno è maggiore o uguale a 0;
}

void Oggetto::usa()
{
	// TODO effect!
}