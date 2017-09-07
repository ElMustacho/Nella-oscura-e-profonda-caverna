#include "Attore.h"
#include <memory>
Attore::Attore(std::string nome, std::vector<std::shared_ptr<Oggetto>> inventario, Attributi attributi, std::vector<std::shared_ptr<Oggetto>> equipaggiamento, double experienceDrop) : Entita(nome,inventario,attributi,equipaggiamento)
{
	this->experienceDrop = experienceDrop;
}

Attore::~Attore()
{

}
