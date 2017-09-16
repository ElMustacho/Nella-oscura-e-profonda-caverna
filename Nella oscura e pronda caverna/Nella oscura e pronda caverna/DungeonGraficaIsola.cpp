#include "DungeonGraficaIsola.h"
#include <iostream>


int DungeonGraficaIsola::playDungeon()
{
	int pianiPercorsi = 0;
	int result;
	
	while (pianiPercorsi < getNumPiani()) {
		piani.push_back(pianoCavernaIsolaGrafica(30,18));
		result = piani.back().playPiano();
		if (result == 1) {
			pianiPercorsi++;
		}
		else
			pianiPercorsi=getNumPiani()+1;
	}
	if (pianiPercorsi == getNumPiani()) {
		return 1; //terminato
	}
	else
		return 0; //non terminato
}

DungeonGraficaIsola::DungeonGraficaIsola(int numPiani, std::string nome, std::string descrizione):Dungeon(numPiani,nome,descrizione)
{

}


DungeonGraficaIsola::~DungeonGraficaIsola()
{
}
