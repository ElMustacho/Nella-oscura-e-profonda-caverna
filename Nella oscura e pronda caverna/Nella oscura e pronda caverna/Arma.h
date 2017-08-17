#pragma once

#include <vector>
#include "Oggetto.h"
#include "Danno.h"
class Arma : public Oggetto
{

public:
	Arma(double peso, std::string nome, std::string descrizione, long valore, Danno danno);
	~Arma();

	Danno getDannoBase()const;

	void setDannoBase(Danno danno);
	Danno attacca() override;
	void Incanta();

	void Deincanta();

private:
	Danno dannoBase;
};

