#pragma once
#include <memory>
#include "Oggetto.h"
#include "Entita.h"
#include "Tileset.h"

class Casella
{

public:
	Casella(Tileset tileset, Oggetto* oggetto, Entita* entità, bool trasparenza, bool attraversabile, int evento); //CHECK quando vuoi dare valori di default, devono essere messi nel .cpp, non nel .h, altrimenti è un casino!
	~Casella();
	void Scava();
	Casella(); //Default
	bool isMuro();
	void setTrasparenza(bool trasparenza) { this->trasparenza = trasparenza; }
	bool isTrasparente() { return this->trasparenza; }
	void setAttraversabile(bool attraversabile) { this->attraversabile = attraversabile; }
	bool isAttraversabile() { return this->attraversabile; }
	Oggetto* getOggetto() { return this->oggetto; }
	Entita* getEntita() { return this->entita; }
	void setOggetto(Oggetto* obj);
	bool setEntita(Entita* entity);

	void doEvento();

private:
	Oggetto* oggetto;
	Entita* entita;
	bool trasparenza;
	bool attraversabile;
	Tileset tileset;
	int evento;

};

