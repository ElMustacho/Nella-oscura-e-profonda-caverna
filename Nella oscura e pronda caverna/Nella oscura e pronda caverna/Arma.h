#pragma once

#include <vector>
#include "Oggetto.h"

class Arma : public Oggetto
{

public:
	Arma(double peso, std::string nome, std::string descrizione, long valore, int danno, std::vector<bool> tipo);
	~Arma();
	virtual void usa();
private:
	int danno;
	std::vector<bool> tipo;
};

