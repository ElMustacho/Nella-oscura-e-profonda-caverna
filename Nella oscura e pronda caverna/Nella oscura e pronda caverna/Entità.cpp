#include "Entità.h"

// FIXME No default constructor for the class "Attributi"
Entità::Entità(std::string nome, Attributi attributi) // FIXME implement & add Attributi()
{
	this->nome = nome;
	this->attributi = attributi;
}


Entità::~Entità()
{
}
