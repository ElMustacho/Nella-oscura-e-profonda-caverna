#pragma once

#include "Oggetto.h"
#include "Entita.h"
#include "Tileset.h"

class Casella
{

public: // CHECK Entit� default constructor error
	Casella(Tileset tileset, Oggetto* oggetto = nullptr, Entita* entit� = nullptr, bool trasparenza = false, bool attraversabile = false, int evento = 0);
	~Casella();

private:
	Oggetto* oggetto;
	Entita* entit�;
	bool trasparenza;
	bool attraversabile;
	Tileset tileset;
	int evento;

};

