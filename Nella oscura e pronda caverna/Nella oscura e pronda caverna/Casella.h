#pragma once

#include "Oggetto.h"
#include "Entita.h"
#include "Tileset.h"

class Casella
{

public: // CHECK Entità default constructor error
	Casella(Tileset tileset, Oggetto* oggetto, Entita* entità, bool trasparenza, bool attraversabile, int evento); //CHECK quando vuoi dare valori di default, devono essere messi nel .cpp, non nel .h, altrimenti è un casino!
	~Casella();

private:
	Oggetto* oggetto;
	Entita* entità;
	bool trasparenza;
	bool attraversabile;
	Tileset tileset;
	int evento;

};

