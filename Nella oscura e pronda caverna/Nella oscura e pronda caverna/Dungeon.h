#pragma once

#include <string>
#include <vector>
#include <memory>
#include <deque>

#include "Piano.h"

class Dungeon
{
public:
	Dungeon(int numPiani, std::string nome, std::string descrizione);
	void generaPiano(int lunghezza, int larghezza, std::vector<std::shared_ptr<Oggetto>> lootPossibile, std::vector<std::shared_ptr<Entita>> entitaPossibili);
	std::string getNome() const { return nome; };
	std::string getDescrizione() const { return descrizione; };
	void setNome(std::string nome) { this->nome = nome; };
	void setDescrizione(std::string descrizione) { this->descrizione = descrizione; };
	int getNumPiani() const { return numPiani; };
	void setNumPiani(int numPiani) { this->numPiani = numPiani; };


private: //TODOFAR Estenderà la/e classe/i x, y, etc.
	int numPiani;
	std::string nome, descrizione;
	std::vector< std::shared_ptr<Piano> > piani;
	//TODO Aggiungi posizioni / estendi

	short int goesWest;
	short int goesNorth;
	short int isUpward;
};