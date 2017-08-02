#pragma once
#include "Piano.h"
class PianoGen :
	public Piano
{
public:
	PianoGen(int larghezza, int lunghezza, std::vector<Oggetto> lootPossibile, std::vector<Entita> entit‡Possibili);
	~PianoGen();
};

