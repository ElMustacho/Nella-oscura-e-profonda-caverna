#include "Entità.h"

Entità::Entità(std::string nome, Attributi attributi) // CHECK manage Attributi
{
	this->nome = nome;
	this->attributi = attributi;
}


Entità::~Entità()
{
}
