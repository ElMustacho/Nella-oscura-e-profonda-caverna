#include "PianoGen.h"



PianoGen::PianoGen(int larghezza, int lunghezza, std::vector<std::shared_ptr<Oggetto>> lootPossibile, std::vector<std::shared_ptr<Entita>> entit�Possibili) : Piano(larghezza,lunghezza,lootPossibile,entit�Possibili)
{
	this->lunghezza = lunghezza;
	this->larghezza = larghezza;
	pavimento.reserve(lunghezza*larghezza); //Velocizza l'accesso futuro alla memoria.
	pavimento = std::vector<Casella>(lunghezza*larghezza, Casella(false)); //Riempio tutto di muri all'inizio
}


PianoGen::~PianoGen()
{
}
