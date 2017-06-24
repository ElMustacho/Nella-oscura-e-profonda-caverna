#include "Casella.h"


// CHECK Entit� & Oggetto
Casella::Casella(Tileset tileset, Oggetto* oggetto, Entita* entit�, bool trasparenza, bool attraversabile, int evento)
{
	this->tileset = tileset;
	this->oggetto = oggetto;
	this->entita = entit�;
	this->trasparenza = trasparenza;
	this->attraversabile = attraversabile;
	this->evento = evento;
}

Casella::Casella() {
	tileset = Tileset(); //FIX ME quando Tileset avr� senso questo dovr� essere qualcosa di concreto.
	oggetto = NULL; //Non c'� nulla di default;
	entita = NULL; //Non c'� nessuno di defalut;
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

void Casella::setOggetto(Oggetto * obj) //TODO gestire la sovrapposizione degli oggetti
{
	this->oggetto = obj;
}

bool Casella::setEntita(Entita * entity) //TODO gestire la sovrapposizione delle entit�, avremo memory leak se cancelliamo la precedente!
{
	if (this->isMuro()) //Quando avremo entit� incorporee questo if dovr� essere alterato
		return false;
	this->entita = entity;
	return true;
}

Casella::~Casella()
{
}

void Casella::Scava() { //per scavare un muro in modo rapido
	tileset = Tileset(); //Da muro a pavimento
	trasparenza = true;
	attraversabile = true;
}