#pragma once
#include <memory>
#include "Oggetto.h"
#include "Entita.h"
#include "Tileset.h"
#include "Protagonista.h"
class Casella
{

public:
	Casella(Tileset tileset, std::list<std::shared_ptr<Oggetto>> oggetti, std::shared_ptr<Entita> entita, bool trasparenza, bool attraversabile, int evento); //CHECK quando vuoi dare valori di default, devono essere messi nel .cpp, non nel .h, altrimenti è un casino!
	~Casella();
	void Scava();
	Casella(bool default); //Default
	bool isMuro();
	void setTrasparenza(bool trasparenza) { this->trasparenza = trasparenza; }
	bool isTrasparente() { return this->trasparenza; }
	void setAttraversabile(bool attraversabile) { this->attraversabile = attraversabile; }
	bool isAttraversabile() { return this->attraversabile; }
	std::list<std::shared_ptr<Oggetto>> getOggetti() { return this->oggetti; }
	std::shared_ptr<Entita> getEntita() { return this->entita; }
	void setOggetti(std::list<std::shared_ptr<Oggetto>> oggetti);
	void pickup();
	void pickup(std::vector<unsigned int> posizioni);
	void drop();
	void drop(std::vector<unsigned int> posizioni);
	std::string descriviOggettiTerra();
	void addOggetto(std::shared_ptr<Oggetto> oggetto);
	void addOggetti(std::vector<std::shared_ptr<Oggetto>> oggetti);
	bool setEntita(std::shared_ptr<Entita> entita);
	void setEvento(int evento) { this->evento = evento; };
	int getEvento() const { return evento; };
	int doEvento();

private:
	std::list<std::shared_ptr<Oggetto>> oggetti;
	std::shared_ptr<Entita> entita;
	bool trasparenza;
	bool attraversabile;
	Tileset tileset;
	int evento;

};

