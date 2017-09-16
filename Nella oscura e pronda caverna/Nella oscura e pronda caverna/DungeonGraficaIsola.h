#pragma once
#include "Dungeon.h"
#include "pianoCavernaIsolaGrafica.h"
class DungeonGraficaIsola :
	public Dungeon
{
public:
	int playDungeon();
	DungeonGraficaIsola(int numPiani, std::string nome, std::string descrizione);
	~DungeonGraficaIsola();
private:
	std::vector<pianoCavernaIsolaGrafica> piani;
};

