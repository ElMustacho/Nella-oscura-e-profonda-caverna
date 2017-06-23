#include "Casella.h"


// CHECK Entit� & Oggetto
Casella::Casella(Tileset tileset, Oggetto* oggetto, Entita* entit�, bool trasparenza, bool attraversabile, int evento)
{
	this->tileset = tileset;
	this->oggetto = oggetto;
	this->entit� = entit�;
	this->trasparenza = trasparenza;
	this->attraversabile = attraversabile;
	this->evento = evento;
}

Casella::Casella() {
	tileset = Tileset(); //FIX ME quando Tileset avr� senso questo dovr� essere qualcosa di concreto.
	oggetto = NULL; //Non c'� nulla di default;
	entit� = NULL; //Non c'� nessuno di defalut;
	trasparenza = false; //Se � una parete non � trasparente
	attraversabile = false; //Se � una parete non � attraversabile
	evento = 0; //Di default non accade nulla
}

bool Casella::isMuro()
{
	if (!attraversabile)
		if(!trasparenza)
			return true;
	return false;
}

Casella::~Casella()
{
}

void Casella::Scava() { //per scavare un muro in modo rapido
	tileset = Tileset(); //Da muro a pavimento
	trasparenza = true;
	attraversabile = true;
}