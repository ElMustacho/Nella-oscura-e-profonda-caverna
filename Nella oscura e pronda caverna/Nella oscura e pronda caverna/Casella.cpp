#include "Casella.h"


// CHECK Entità & Oggetto
Casella::Casella(Tileset tileset, Oggetto* oggetto, Entita* entità, bool trasparenza, bool attraversabile, int evento)
{
	this->tileset = tileset;
	this->oggetto = oggetto;
	this->entità = entità;
	this->trasparenza = trasparenza;
	this->attraversabile = attraversabile;
	this->evento = evento;
}

Casella::Casella() {
	tileset = Tileset(); //FIX ME quando Tileset avrà senso questo dovrà essere qualcosa di concreto.
	oggetto = NULL; //Non c'è nulla di default;
	entità = NULL; //Non c'è nessuno di defalut;
	trasparenza = false; //Se è una parete non è trasparente
	attraversabile = false; //Se è una parete non è attraversabile
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