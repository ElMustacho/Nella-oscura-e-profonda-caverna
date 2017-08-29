#pragma once
#include "Piano.h"
class PianoGen :
	public Piano
{
public:
	PianoGen(int larghezza, int lunghezza, std::vector<std::shared_ptr<Oggetto>> lootPossibile, std::vector<std::shared_ptr<Entita>> entit‡Possibili);
	~PianoGen();
};

