#include "Attore.h"




Attore::Attore(std::string nome, std::list<Oggetto> inventario, Attributi attributi, std::vector<Oggetto> equipaggiamento, double experienceDrop) : Entita(nome,inventario,attributi,equipaggiamento)

{
	this->experienceDrop = experienceDrop;
}


Attore::~Attore()
{
}
