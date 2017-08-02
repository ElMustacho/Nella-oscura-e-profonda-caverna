#pragma once
#include "Piano.h"
class PianoFile :
	public Piano
{
public:
	PianoFile(std::string posizione, bool &successo);
	~PianoFile();
};

