#pragma once
#include "Piano.h"
class PianoFile :
	public Piano
{
public:
	bool spargiLoot(std::vector<cood> posizioniValide);
	PianoFile(std::string posizione, bool &successo);
	~PianoFile();
};

