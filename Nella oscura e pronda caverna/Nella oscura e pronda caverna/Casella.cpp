#include "Casella.h"


// CHECK Entità & Oggetto
Casella::Casella(Tileset tileset, Oggetto* oggetto, Entita* entità, bool trasparenza, bool attraversabile, int evento)
{
	this->tileset = tileset;
	this->oggetto = oggetto;
	this->entita = entità;
	this->trasparenza = trasparenza;
	this->attraversabile = attraversabile;
	this->evento = evento;
}

Casella::Casella() {
	tileset = Tileset(); //FIX ME quando Tileset avrà senso questo dovrà essere qualcosa di concreto.
	oggetto = NULL; //Non c'è nulla di default;
	entita = NULL; //Non c'è nessuno di defalut;
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

void Casella::setOggetto(Oggetto * obj) //TODO gestire la sovrapposizione degli oggetti
{
	this->oggetto = obj;
}

bool Casella::setEntita(Entita * entity) //TODO gestire la sovrapposizione delle entità, avremo memory leak se cancelliamo la precedente!
{
	if (this->isMuro()) //Quando avremo entità incorporee questo if dovrà essere alterato
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