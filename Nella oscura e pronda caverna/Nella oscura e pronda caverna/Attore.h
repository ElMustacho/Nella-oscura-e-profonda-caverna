#pragma once
#include "Entità.h"
class Attore : public Entità
{

public:
	Attore(std::string nome, Attributi attributi, double experienceDrop);
	~Attore();

private:
	double experienceDrop;
};

