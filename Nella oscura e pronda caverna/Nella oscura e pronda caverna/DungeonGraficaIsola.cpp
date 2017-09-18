#include "DungeonGraficaIsola.h"
#include <iostream>


int DungeonGraficaIsola::playDungeon()
{
	int pianiPercorsi = 0;
	int result;
	std::vector<std::shared_ptr<Oggetto>> oggettiInseribili;
	auto oggetto = std::make_shared<Oggetto>(1, "Quaderno degli appunti", "Appartenente in precedenza ad sociopatico ragazzo giapponese con deliri di onnipotenza", 15);
	auto oggetto2 = std::make_shared<Arma>(3, "Ascia bipenne", "Forgiata con due penne bic", 14, Danno(std::vector<double>{1}, 15));
	auto oggetto3 = std::make_shared<Oggetto>(1, "Sacchetto di polvere", "Made in Colombia", 150);
	auto oggetto4 = std::make_shared<Arma>(0.5, "Pugnale piramidale", "Se ci fossero le convenzioni di Ginevra questo pugnale le infrangerebbe", 9, Danno(std::vector<double>{1}, 25));
	oggettiInseribili.push_back(oggetto);
	oggettiInseribili.push_back(oggetto2);
	oggettiInseribili.push_back(oggetto3);
	oggettiInseribili.push_back(oggetto4);

	while (pianiPercorsi < getNumPiani()) {
		piani.push_back(pianoCavernaIsolaGrafica(30,18,"",oggettiInseribili));
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
