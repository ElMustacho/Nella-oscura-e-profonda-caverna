#include "Dungeon.h"

Dungeon::Dungeon(int numPiani, std::string nome, std::string descrizione)
{
	if (numPiani > 0)
	{
		this->numPiani = numPiani;
	}
	else
	{
		this->numPiani = 1;
	}
	this->nome = nome;
	this->descrizione = descrizione;
}

void Dungeon::generaPiano(int lunghezza, int larghezza, std::vector<std::shared_ptr<Oggetto>> lootPossibile, std::vector<std::shared_ptr<Entita>> entitaPossibili)
{
	std::shared_ptr<Piano> p( new Piano(lunghezza, larghezza, lootPossibile, entitaPossibili) );
	this->piani.push_back( p );

}
