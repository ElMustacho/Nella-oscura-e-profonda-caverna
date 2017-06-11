#pragma once

#include "Oggetto.h"
#include "Entit�.h"
#include "Tileset.h"

class Casella
{

public: // CHECK Entit� default constructor error
	Casella(Tileset tileset, Oggetto* oggetto = nullptr, Entit� entit� = NULL, bool trasparenza = false, bool attraversabile = false, int evento = 0);
	~Casella();

private:
	Oggetto* oggetto;
	Entit� entit�;
	bool trasparenza;
	bool attraversabile;
	Tileset tileset;
	int evento;

};

