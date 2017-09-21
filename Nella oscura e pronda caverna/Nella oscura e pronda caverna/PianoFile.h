#pragma once
#include "Piano.h"
class PianoFile :
	public Piano
{
public:
	bool rSpargiLoot(std::vector<cood> posizioniValide);
	PianoFile(std::string posizione, bool &successo);
	~PianoFile();
};

