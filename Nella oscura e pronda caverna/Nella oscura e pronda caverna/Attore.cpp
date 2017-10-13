#include "Attore.h"
#include <memory>

Attore::Attore(std::string nome, std::vector<std::shared_ptr<Oggetto>> inventario, Attributi attributi, Equipaggiamento equipaggiamento, double experienceDrop, std::string posToFile) : Entita(nome, inventario, attributi, equipaggiamento, posToFile)
{
	this->experienceDrop = experienceDrop;
}


Attore::~Attore()
{

}
