#pragma once
#include "PianoFile.h"
class PianoFileGrafica :
	public PianoFile
{
	
public:
	void stampaPianoSuFinestra();
	PianoFileGrafica(std::string posizione, bool success, std::string pathToFile="");
	~PianoFileGrafica();
};

