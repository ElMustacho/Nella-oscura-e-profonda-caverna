#pragma once
#include "Entita.h"
class Attore : public Entita
{

public:
	Attore(std::string nome, std::vector<std::shared_ptr<Oggetto>> inventario, Attributi attributi, Equipaggiamento equipaggiamento, double experienceDrop);
	~Attore();

private:
	double experienceDrop;
};

