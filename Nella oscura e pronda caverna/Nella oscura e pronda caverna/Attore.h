#pragma once
#include "Entit�.h"
class Attore : public Entit�
{

public:
	Attore(std::string nome, Attributi attributi, double experienceDrop);
	~Attore();

private:
	double experienceDrop;
};

