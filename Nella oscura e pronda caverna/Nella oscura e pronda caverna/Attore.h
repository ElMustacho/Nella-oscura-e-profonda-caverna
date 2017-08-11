#pragma once
#include "Entita.h"
class Attore : public Entita
{

public:
	Attore(std::string nome, std::list<Oggetto> inventario, Attributi attributi, std::vector<Oggetto> equipaggiamento, double experienceDrop);
	~Attore();

private:
	double experienceDrop;
};

