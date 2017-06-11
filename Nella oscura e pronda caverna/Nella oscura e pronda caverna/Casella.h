#pragma once

#include "Oggetto.h"
#include "Entità.h"
#include "Tileset.h"

class Casella
{

public: // CHECK Entità default constructor error
	Casella(Tileset tileset, Oggetto* oggetto = nullptr, Entità entità = NULL, bool trasparenza = false, bool attraversabile = false, int evento = 0);
	~Casella();

private:
	Oggetto* oggetto;
	Entità entità;
	bool trasparenza;
	bool attraversabile;
	Tileset tileset;
	int evento;

};

