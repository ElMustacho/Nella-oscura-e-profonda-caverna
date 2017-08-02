#pragma once
#include <list>
#include "Oggetto.h"


class Scrigno :	public Oggetto
{

public:
	Scrigno(double peso, std::string nome, std::string descrizione, long valore, int unlock, std::list<Oggetto> loot);
	~Scrigno();

	void open();
	std::list<Oggetto> prendiOggetto(Oggetto* scelta = nullptr);
	void inserisciOggetto(Oggetto* obj);

private:
	std::list<Oggetto> loot;
	int unlock; // 0 = aperto, >0 = metodi apertura/chiuso

};

