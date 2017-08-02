#include "PianoGen.h"



PianoGen::PianoGen(int larghezza, int lunghezza, std::vector<Oggetto> lootPossibile, std::vector<Entita> entitąPossibili) : Piano(larghezza,lunghezza,lootPossibile,entitąPossibili)
{
	this->lunghezza = lunghezza;
	this->larghezza = larghezza;
	pavimento.reserve(lunghezza*larghezza); //Velocizza l'accesso futuro alla memoria.
	pavimento = std::vector<Casella>(lunghezza*larghezza, Casella(false)); //Riempio tutto di muri all'inizio
}


PianoGen::~PianoGen()
{
}
