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


Casella::~Casella()
{
}
