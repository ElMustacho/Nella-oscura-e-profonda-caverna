#include "Attore.h"




Attore::Attore(std::string nome, std::vector<Oggetto> inventario, Attributi attributi, std::vector<Oggetto> equipaggiamento, double experienceDrop) : Entita(nome,inventario,attributi,equipaggiamento)

{
	this->experienceDrop = experienceDrop;
}


Attore::~Attore()
{
}
