#pragma once
#include <list>
#include "Oggetto.h"


class Scrigno :	public Oggetto
{

public:
	Scrigno(int unlock, std::list<Oggetto> loot);
	~Scrigno();

	void open();
	std::list<Oggetto> prendiOggetto(Oggetto* scelta = nullptr);

private:
	std::list<Oggetto> loot;
	int unlock; // 0 = aperto, >0 = metodi apertura/chiuso

};

