#include <iostream>
#include <ctime>
#include "Oggetto.h"
#include "Entita.h"
#include "Piano.h"
#include "PianoFile.h"
#include "Danno.h"
#include "pianoCavernaIsola.h"
int main() 
{
	std::list<Oggetto> tabellaLoot; //VUOTA
	std::vector<Oggetto> Equipaggiamento;
	std::vector<Entita> tabellaEntita; //VUOTA
	cood coord(5, 5);
	Attributi dexAlta(4, 14, 4, 4, 4, 4, 4, 1);
	Protagonista Saitama("Saitama", tabellaLoot, dexAlta, Equipaggiamento, 1, 1094.6099, 400); //Sto usando tabella loot giusto perchè è vuota
	pianoCavernaIsola please(20, 20);
	please.StampaChar();
	bool ok = true;
	PianoFile pregen("testPreload.txt", ok);
	if (!ok)
	{
		std::cout << "Merda";
		return -1;
	}
	//else
		//pregen.StampaChar();
	char a ='0', b = '0'; //TODO così sono brutto e gestito male
	std::cout << "Bloat text? y/n: ";
	while(a!='y'&&a!='n')
		std::cin >> a;
	std::cout << "Autopickup? y/n: ";
	while (b != 'y'&&b != 'n')
		std::cin >> b;
	Attore JimBob("JimBob", tabellaLoot, Attributi(), Equipaggiamento, 4.);
	pregen.at(5, 5).setEntita(&Saitama);
	pregen.at(2, 6).setEntita(&JimBob);
	auto controllo = pregen.floodFill(coord);
	Oggetto oggettoDebug(10.,"Cosa", "Qualcosa di fantastico", 40);
	Oggetto oggettoDebug2(5., "Altra cosa", "Qualcosa di altrettanti fantastico", 15);
	Saitama.addInventario(oggettoDebug);
	pregen.at(5,5).getEntita()->addInventario(oggettoDebug2);
	std::cout << pregen.at(5, 5).getEntita()->describeInventario() << std::endl;
	pregen.at(4, 9).setEvento(1);
	/*
	Attributi dexAlta(4, 14, 4, 4, 4, 4, 4, 1);
	Saitama.setAttributi(dexAlta);
	std::cout << Saitama.getAttributi().getDestrezza() << std::endl;
	*/
	int exit = 0;
	int X = 5, Y = 5;
	std::cout << std::endl;
	while (exit == 0) {
		pregen.StampaChar();
		if (a=='y')
			std::cout << std::endl << "Usa il tastierino numerico per muoverti, 5 per uscire: ";
		char direzione;
		std::cin >> direzione;
		std::cout << std::endl;
		system("CLS");
		switch (direzione)
		{
		case '1':
			if (pregen.muoviEntita(X, Y, X - 1, Y + 1) == 0) {
				if (a == 'y')
					std::cout << "Ho provato a muovermi con successo." << std::endl;
				X--;
				Y++;
				//TODO fammi funzionare a modo
				//if (b == 'y')
					//pregen.at(X, Y).getEntita()->addInventario(pregen.at(X, Y).getOggetto();
			}
			break;
		case '2':
			if (pregen.muoviEntita(X, Y, X, Y + 1) == 0) {
				if (a == 'y')
					std::cout << "Ho provato a muovermi con successo." << std::endl; 
				Y++;
			}
			break;
		case '3':
			if (pregen.muoviEntita(X, Y, X + 1, Y + 1) == 0) {
				if (a == 'y')
					std::cout << "Ho provato a muovermi con successo." << std::endl;
				X++;
				Y++;
			}
			break;
		case '4':
			if (pregen.muoviEntita(X, Y, X - 1, Y) == 0) {
				if (a == 'y')
					std::cout << "Ho provato a muovermi con successo." << std::endl;
				X--;
			}
			break;
		case '5':
			exit++;
			break;
		case '6':
			if (pregen.muoviEntita(X, Y, X + 1, Y) == 0) {
				if (a == 'y')
					std::cout << "Ho provato a muovermi con successo." << std::endl;
				X++;
			}
			break;
		case '7':
			if (pregen.muoviEntita(X, Y, X - 1, Y - 1) == 0) {
				if (a == 'y')
					std::cout << "Ho provato a muovermi con successo." << std::endl;
				X--;
				Y--;
			}
			break;
		case '8':
			if (pregen.muoviEntita(X, Y, X, Y - 1) == 0) {
				if (a == 'y')
					std::cout << "Ho provato a muovermi con successo." << std::endl;
				Y--;
			}
			break;
		case '9':
			if (pregen.muoviEntita(X, Y, X + 1, Y - 1) == 0) {
				if (a == 'y')
					std::cout << "Ho provato a muovermi con successo." << std::endl;
				X++;
				Y--;
			}
			break;

		default:
			if (a == 'y')
				std::cout << "Input non valido" << std::endl;

		}
	}
	pregen.StampaChar();
	std::cout << std::endl;
	std::cin >> a;
	
}