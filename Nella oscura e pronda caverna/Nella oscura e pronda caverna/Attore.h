#pragma once
#include "Entita.h"
class Attore : public Entita
{

public:
	Attore(std::string nome, Attributi attributi, double experienceDrop);
	~Attore();

private:
	double experienceDrop;
};

