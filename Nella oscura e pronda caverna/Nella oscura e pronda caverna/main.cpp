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
#include "TextBox.h"

#include "StatoProtagonista.h"
#include "DisplayStatoProtagonista.h"

int main()
{
	//std::vector<std::shared_ptr<Oggetto>> tabellaLoot; // VUOTA
	//Equipaggiamento equipaggiamento;
	//Attributi normale(4, 4, 4, 4, 4, 4, 4, 4);
	//Protagonista Saitama("Saitama", tabellaLoot, normale, equipaggiamento, 1, 1094.6099, 400); // Sto usando tabella loot giusto perchè è vuota



	StatoProtagonista stato;
	stato.setStato(10, 200, 600);
	DisplayStatoProtagonista statoDisplay(&stato); // std::make_shared<StatoProtagonista>(stato)

	//HACK temp solution it should register/remove the observer inside statoDisplay
	//auto shrdStatus = std::make_shared<DisplayStatoProtagonista>(statoDisplay);

	//stato.registerObserver(shrdStatus); // std::make_shared<DisplayStatoProtagonista>(statoDisplay) 
	stato.setStato(5, 100, 500);
	//stato.removeObserver(shrdStatus); // std::make_shared<DisplayStatoProtagonista>(statoDisplay)

	std::cout << stato.numObservers() << std::endl; 
	getchar();
	


	/*
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
	return 0;
	/*bool ok = true;*/
	//PianoFile pregen("testPreload.txt", ok);
	//if (!ok)
	//{
	//	std::cout << "Medda";
	//	return -1;
	//}	
	
}