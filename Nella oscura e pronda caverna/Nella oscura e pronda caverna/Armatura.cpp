#include "Armatura.h"



Armatura::Armatura(double peso, std::string nome, std::string descrizione, long valore, Danno resistenzaConferita):Oggetto(peso, nome,descrizione,valore)
{
	this->resistenzaConferita = resistenzaConferita;
}


Armatura::~Armatura()
{
}
