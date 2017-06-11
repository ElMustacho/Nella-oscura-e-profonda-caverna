#include "Attore.h"



Attore::Attore(std::string nome, Attributi attributi, double experienceDrop) : Entità(nome, attributi)
{
	this->experienceDrop = experienceDrop;
}


Attore::~Attore()
{
}
