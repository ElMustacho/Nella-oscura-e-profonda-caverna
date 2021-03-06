#include "DungeonGraficaIsola.h"
#include <iostream>
#include "UtilityGrafica.h"

int DungeonGraficaIsola::playDungeon()
{
	int pianiPercorsi = 0;
	int result;
	std::vector<std::shared_ptr<Entita>> entitaGenerabili;
	/////////////////////////
	
	std::vector<std::shared_ptr<Oggetto>> inventario;
	Attributi scarso(3, 4, 2, 2, 2, 1, 3, 1);
	Equipaggiamento equipaggiamento;
	auto mazzaDiStagno = std::make_shared<Arma> (0.25, "Mazza poco dura", "Probabilmente � meglio usare i pugni", 2, Danno({ 0,0,1 }, 4));
	equipaggiamento.equipaggia(mazzaDiStagno);
	auto appoggio1 = std::make_shared<Attore>("Goblin scansafatiche", inventario, scarso, equipaggiamento, 1.1);
	auto appoggio2 = std::make_shared<Attore>("Goblin indecente", inventario, scarso, equipaggiamento, 1.1);
	auto appoggio3 = std::make_shared<Attore>("Goblin ammazzatopi", inventario, scarso, equipaggiamento, 1.1);
	entitaGenerabili.push_back(appoggio1);
	entitaGenerabili.push_back(appoggio2);
	entitaGenerabili.push_back(appoggio3);

	/////////////////////////
	std::vector<std::shared_ptr<Oggetto>> oggettiInseribili;
	auto oggetto = std::make_shared<Oggetto>(1, "Quaderno degli appunti", "Appartenente in precedenza ad un sociopatico ragazzo giapponese con deliri di onnipotenza", 25);
	auto oggetto2 = std::make_shared<Arma>(3, "Ascia bipenne", "Forgiata con due penne bic", 14, Danno(std::vector<double>{1}, 15));
	auto oggetto3 = std::make_shared<Oggetto>(1, "Sacchetto di polvere", "Made in Colombia", 150);
	auto oggetto4 = std::make_shared<Arma>(0.5, "Pugnale piramidale", "Se ci fossero le convenzioni di Ginevra questo pugnale le infrangerebbe", 9, Danno(std::vector<double>{1}, 40));
	oggettiInseribili.push_back(oggetto);
	oggettiInseribili.push_back(oggetto2);
	oggettiInseribili.push_back(oggetto3);
	oggettiInseribili.push_back(oggetto4);
	std::shared_ptr<Protagonista> player=nullptr;
	while (pianiPercorsi < getNumPiani()) {
		piani.push_back(pianoCavernaIsolaGrafica(30,18,"",oggettiInseribili,player,entitaGenerabili));
		player = std::dynamic_pointer_cast<Protagonista>(piani.back().getVectorEntita().at(0));
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
