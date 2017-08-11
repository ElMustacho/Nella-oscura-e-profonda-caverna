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
bool Oggetto::operator==(const Oggetto rOggetto) const
{
	if (typeid(this) == typeid(rOggetto))
		if (this->nome == rOggetto.nome)
			if (this->peso == rOggetto.peso)
				if (this->descrizione == rOggetto.descrizione)
					if (this->valore == rOggetto.valore)
						return true;
	return false;
}
void Oggetto::usa()
{
	// TODO effect!
}