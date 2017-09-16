#include <iostream>
#include <ctime>
#include <memory>
#include <deque>
#include "Oggetto.h"
#include "Entita.h"
#include "Piano.h"
#include "PianoFile.h"
#include "Danno.h"
#include "pianoCavernaIsola.h"
#include "PianoFileGrafica.h"
#include "pianoCavernaIsolaGrafica.h"
#include "SFML\Graphics.hpp"
#include "DungeonGraficaIsola.h"
int main()
{
	
	DungeonGraficaIsola primoDungeon(3, "Il primo dungeon", "Il primo dell'avventura");
	auto result=primoDungeon.playDungeon();
	if (result == 1)
		std::cout << "Congratulazioni!" << std::endl;
	else if (result == 0) {
		std::cout << "Codardo!" << std::endl;
	}

	std::vector<std::shared_ptr<Oggetto>> tabellaLoot; //VUOTA
	Equipaggiamento Equipaggiamento;
	std::vector<Entita> tabellaEntita; //VUOTA
	cood coord(5, 5);
	Attributi dexAlta(4, 4, 4, 4, 4, 4, 4, 1);
	Attributi normale(4, 4, 4, 4, 4, 4, 4, 4);
	Protagonista Saitama("Saitama", tabellaLoot, normale, Equipaggiamento, 1, 1094.6099, 400); //Sto usando tabella loot giusto perchè è vuota
	pianoCavernaIsolaGrafica please(20, 20);
	please.stampaPianoSuFinestra();
	please.playPiano();
	bool ok = true;
	PianoFile pregen("testPreload.txt", ok);
	if (!ok)
	{
		std::cout << "Medda";
		return -1;
	}
	//else
	//pregen.StampaChar();
	

	PianoFileGrafica mappaGrafica("testPreload.txt", ok);
	mappaGrafica.StampaChar();
	mappaGrafica.stampaPianoSuFinestra();

	Attore JimBob("JimBob", tabellaLoot, dexAlta, Equipaggiamento, 4.);
	Attore Orco("Orco", tabellaLoot, dexAlta, Equipaggiamento, 4.);

	/*
	pregen.at(5, 5).setEntita(std::make_shared<Protagonista>(Saitama));
	pregen.at(6, 2).setEntita(std::make_shared<Attore>(JimBob));
	*/
	Attore Perseo("Perseo", tabellaLoot, dexAlta, Equipaggiamento, 9.);
	auto controllo = pregen.floodFill(coord);
	pregen.placeEntita(std::make_shared<Protagonista>(Saitama), cood(5, 5));
	pregen.placeEntita(std::make_shared<Attore>(Orco), cood(24, 9));
	
	pregen.placeEntita(std::make_shared<Attore>(JimBob), cood(31, 7));
	pregen.placeEntita(std::make_shared<Attore>(Perseo), cood(22, 9));
	Oggetto oggettoDebug(10., "Cosa", "Qualcosa di fantastico", 40);
	Oggetto oggettoDebug2(5., "Altra cosa", "Qualcosa di altrettanto fantastico", 15);
	Saitama.addInventario(std::make_shared<Oggetto>(oggettoDebug));
	pregen.at(5, 5).getEntita()->addInventario(std::make_shared<Oggetto>(oggettoDebug2)); //FIXME sballo se non ho valori validi
	std::cout << std::endl << pregen.at(5, 5).getEntita()->describeInventario() << std::endl; //FIXME same
	/*
	Attributi dexAlta(4, 14, 4, 4, 4, 4, 4, 1);
	Saitama.setAttributi(dexAlta);
	std::cout << Saitama.getAttributi().getDestrezza() << std::endl;
	*/
	pregen.spargiLoot(pregen.floodFill(cood(5, 5)));
	auto g = pregen.playPiano();
	if (g == 1) {
		std::cout << "HHHHHHHHHMMMMMMMMM" << std::endl;
	}
	else if (g == 0)
	{
		std::cout << "Gunga Runga" << std::endl;
	}
	
}