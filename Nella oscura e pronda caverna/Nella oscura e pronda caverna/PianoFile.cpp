#include "PianoFile.h"
#include <fstream>
#include <iostream>

PianoFile::PianoFile(std::string posizione, bool &successo) : Piano()
{
	std::ifstream inputPiano(posizione);
	std::string lineaCaselle;
	lunghezza = 0, larghezza = 0;
	for (int i = 0; std::getline(inputPiano, lineaCaselle); i++)
	{
		for (unsigned int j = 0; j < lineaCaselle.size(); j++)
		{
			if (lineaCaselle.at(j) == '#')
				pavimento.push_back(Casella(false));
			else if (lineaCaselle.at(j) == '.')
				pavimento.push_back(Casella(true));
			else {
				std::cout << "E' successo un casino.\n";
				successo = false;
			}
		}
		if (i == 0)
			larghezza = lineaCaselle.size();
		lunghezza++;
	}
	pavimento.reserve(lunghezza*larghezza); //LOOKATME questa chiamata è molto importante, e deve essere fatta alla fine di ogni costruttore!
	//TODO addobjects
}


PianoFile::~PianoFile()
{
}
