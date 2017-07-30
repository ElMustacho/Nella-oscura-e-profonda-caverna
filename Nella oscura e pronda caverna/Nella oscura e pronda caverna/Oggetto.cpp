#include "Oggetto.h"
#include <cmath>
Oggetto::~Oggetto()
{
}

Danno Oggetto::attacca() {
	std::vector<double> tmp;
	return Danno(tmp,1 + log(peso)); // a meno che il peso non sia negativo il danno è maggiore o uguale a 0;
	

}

void Oggetto::usa()
{
	// TODO effect!
}