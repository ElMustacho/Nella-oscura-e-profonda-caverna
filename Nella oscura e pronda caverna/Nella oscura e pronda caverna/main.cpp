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
#include "SerraturaFOS.h"
int main()
{
	SerraturaFOS test(90,15);
	int resultLadro=test.scassina();
	if (resultLadro == 0) {
		std::cout << "Incapace!" << std::endl;
	}
	else if (resultLadro == 1)
	{
		std::cout << "Bravo!" << std::endl;
	}
	else
		std::cout << "WTF?" << std::endl;

	DungeonGraficaIsola primoDungeon(3, "Il primo dungeon", "Il primo dell'avventura");
	auto result=primoDungeon.playDungeon();
	if (result == 1)
		std::cout << "Congratulazioni!" << std::endl;
	else if (result == 0) {
		std::cout << "Codardo!" << std::endl;
	}
	getchar();
	return 0;
	// È fortemente consigliato non rimuovere il commento finché non saranno corretti i problemi sulla view
	/*
	std::vector<std::shared_ptr<Oggetto>> tabellaLoot; //VUOTA
	Equipaggiamento Equipaggiamento;
	std::vector<Entita> tabellaEntita; //VUOTA
	coord coord(5, 5);
	Attributi dexAlta(4, 4, 4, 4, 4, 4, 4, 1);
	Attributi normale(4, 4, 4, 4, 4, 4, 4, 4);
	Protagonista Saitama("Saitama", tabellaLoot, normale, Equipaggiamento, 1, 1094.6099, 400); //Sto usando tabella loot giusto perchè è vuota
	pianoCavernaIsolaGrafica please(20, 20);
	please.playPiano();
	*/
	
	/*bool ok = true;*/
	//PianoFile pregen("testPreload.txt", ok);
	//if (!ok)
	//{
	//	std::cout << "Medda";
	//	return -1;
	//}	
	
}