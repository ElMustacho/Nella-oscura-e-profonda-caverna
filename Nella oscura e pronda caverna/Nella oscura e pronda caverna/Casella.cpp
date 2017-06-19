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


Casella::~Casella()
{
}
