#include <iostream>
#include <ctime>
#include "Oggetto.h"
#include "Entita.h"
#include "Piano.h"
#include "PianoFile.h"
#include "Danno.h"
int main() 
{
	bool ok = true;
	for (unsigned int i = 0; i < Danno::giveCategoriaDanni().size(); i++)
		std::cout << Danno::giveCategoriaDanni()[i] << std::endl;
	PianoFile pregen("testPreload.txt", ok);
	if (!ok)
	{
		std::cout << "Merda";
		return -1;
	}
	else
		pregen.StampaChar();
	char a ='0', b = '0'; //TODO così sono brutto e gestito male
	std::cout << "Bloat text? y/n: ";
	while(a!='y'&&a!='n')
		std::cin >> a;
	std::cout << "Autopickup? y/n: ";
	while (b != 'y'&&b != 'n')
		std::cin >> b;
	std::vector<Oggetto> tabellaLoot; //VUOTA
	std::vector<Entita> tabellaEntita; //VUOTA
	Protagonista Saitama("Saitama", tabellaLoot, Attributi(), tabellaLoot, 1, 0., 0); //Sto usando tabella loot giusto perchè è vuota
	Attore JimBob("JimBob", tabellaLoot, Attributi(), tabellaLoot, 4.);
	pregen.at(1, 5).setEntita(&Saitama);
	pregen.at(2, 6).setEntita(&JimBob);
	Oggetto oggettoDebug(10.,"Cosa", "Qualcosa di fantastico", 40);
	Oggetto oggettoDebug2(5., "Altra cosa", "Qualcosa di altrettanti fantastico", 15);
	Saitama.addInventario(oggettoDebug);
	Saitama.addInventario(oggettoDebug2);
	std::cout << pregen.at(1, 5).getEntita()->describeInventario() << std::endl;
	/*
	Attributi dexAlta(4, 14, 4, 4, 4, 4, 4, 1);
	Saitama.setAttributi(dexAlta);
	std::cout << Saitama.getAttributi().getDestrezza() << std::endl;
	*/
	int exit = 0;
	int X = 5, Y = 1;
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
			std::cout << "Input non valido" << std::endl;

		}
	}
	pregen.StampaChar();
	std::cout << std::endl;
	std::cin >> a;
	//Entita player1("Pippo",Attributi()); // Il costruttore vuoto di Attributi non deve esistere
	//std::cout << "Giocatore: " << player1.getNome() << std::endl;
	/*
	Oggetto idolo(15., "Hatkanda", "L'oggetto di un film generico", 400); 
	std::cout << idolo.getDescrizione() << std::endl << idolo.getNome() << std::endl << idolo.getPeso() << std::endl <<
		idolo.getValore();
	char a = 0;
	std::vector<Oggetto> tabellaLoot; //VUOTA
	std::vector<Entita> tabellaEntita; //VUOTA
	Protagonista Saitama("Saitama",tabellaLoot,Attributi(),tabellaLoot,1,0.,0); //Sto usando tabella loot giusto perchè è vuota
	Attore JimBob("JimBob",tabellaLoot,Attributi(),tabellaLoot,4.);
	Piano primoLivello(10, 8, 1, tabellaLoot, tabellaEntita);
	primoLivello.creaStanzaRettangolare(2, 2, 5, 5);
	primoLivello.at(5, 5).setEntita(&Saitama);
	primoLivello.at(3, 3).setEntita(&JimBob);
	int exit = 0;
	int X = 5, Y = 5;
	std::cout << std::endl;
	while (exit == 0) {
		primoLivello.StampaChar();
		std::cout << std::endl << "Usa il tastierino numerico per muoverti, 5 per uscire: ";
		char direzione;
		std::cin >> direzione;
		std::cout << std::endl;
		system("CLS");
		switch (direzione)
		{
		case '1':
			if (primoLivello.muoviEntita(X, Y, X - 1, Y + 1) == 0) {
				std::cout << "Ho provato a muovermi con successo." << std::endl;
				X--;
				Y++;
			}
			break;
		case '2':
			if (primoLivello.muoviEntita(X, Y, X, Y + 1) == 0) {
				std::cout << "Ho provato a muovermi con successo." << std::endl;
				Y++;
			}
			break;
		case '3':
			if (primoLivello.muoviEntita(X, Y, X + 1, Y + 1) == 0) {
				std::cout << "Ho provato a muovermi con successo." << std::endl;
				X++;
				Y++;
			}
			break;
		case '4':
			if (primoLivello.muoviEntita(X, Y, X - 1, Y) == 0) {
				std::cout << "Ho provato a muovermi con successo." << std::endl;;
				X--;
			}
			break;
		case '5':
			exit++;
			break;
		case '6':
			if (primoLivello.muoviEntita(X, Y, X + 1, Y) == 0) {
				std::cout << "Ho provato a muovermi con successo." << std::endl;;
				X++;
			}
			break;
		case '7':
			if (primoLivello.muoviEntita(X, Y, X - 1, Y - 1) == 0) {
				std::cout << "Ho provato a muovermi con successo." << std::endl;
				X--;
				Y--;
			}
			break;
		case '8':
			if (primoLivello.muoviEntita(X, Y, X, Y - 1) == 0) {
				std::cout << "Ho provato a muovermi con successo." << std::endl;
				Y--;
			}
			break;
		case '9':
			if (primoLivello.muoviEntita(X, Y, X + 1, Y - 1) == 0) {
				std::cout << "Ho provato a muovermi con successo." << std::endl;
				X++;
				Y--;
			}
			break;
		
		default:
			std::cout << "Input non valido" << std::endl;
			
		}
	}
	primoLivello.StampaChar();
	//primoLivello.StampaFileChar();
	std::cout << std::endl;
	std::cin >> a;
  //Questo main dovrà finire in un test.*/
}