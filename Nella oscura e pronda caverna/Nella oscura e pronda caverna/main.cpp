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
int main()
{
	std::list<std::shared_ptr<Oggetto>> tabellaLoot; //VUOTA
	std::vector<std::shared_ptr<Oggetto>> Equipaggiamento;
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
		std::cout << "Medda";
		return -1;
	}
	//else
	//pregen.StampaChar();
	char a = '0', b = '0'; //TODO così sono brutto e gestito male
	std::cout << "Bloat text? y/n: ";
	while (a != 'y'&&a != 'n')
		std::cin >> a;
	std::cout << "Autopickup? y/n: ";
	while (b != 'y'&&b != 'n')
		std::cin >> b;

	Attore JimBob("JimBob", tabellaLoot, dexAlta, Equipaggiamento, 4.);
	/*
	pregen.at(5, 5).setEntita(std::make_shared<Protagonista>(Saitama));
	pregen.at(6, 2).setEntita(std::make_shared<Attore>(JimBob));
	*/
	Attore Perseo("Perseo", tabellaLoot, dexAlta, Equipaggiamento, 9.);
	auto controllo = pregen.floodFill(coord);
	pregen.placeEntita(std::make_shared<Protagonista>(Saitama), cood(5, 5));
	pregen.placeEntita(std::make_shared<Attore>(JimBob), cood(31, 7));
	pregen.placeEntita(std::make_shared<Attore>(Perseo), cood(22, 9));
	Oggetto oggettoDebug(10., "Cosa", "Qualcosa di fantastico", 40);
	Oggetto oggettoDebug2(5., "Altra cosa", "Qualcosa di altrettanti fantastico", 15);
	Saitama.addInventario(std::make_shared<Oggetto>(oggettoDebug));
	pregen.at(5, 5).getEntita()->addInventario(std::make_shared<Oggetto>(oggettoDebug2)); //FIXME sballo se non ho valori validi
	std::cout << std::endl << pregen.at(5, 5).getEntita()->describeInventario() << std::endl; //FIXME same
	std::cout << "Premi k per ammazzare l'asterisco al primo turno" << std::endl;
	/*
	Attributi dexAlta(4, 14, 4, 4, 4, 4, 4, 1);
	Saitama.setAttributi(dexAlta);
	std::cout << Saitama.getAttributi().getDestrezza() << std::endl;
	*/
	pregen.spargiLoot(pregen.floodFill(cood(5, 5)));
	int exit = 0;
	auto stuff = pregen.getPositionOfPlayer();
	int X = stuff.first, Y = stuff.second;
	std::cout << std::endl;
	std::deque<std::pair<std::shared_ptr<Entita>, cood>> pilaTurni;
	auto et = pregen.getVectorEntita();
	auto po = pregen.getVectorPosizioni();
	bool goAhead = true, goPlayer = true;
	for (unsigned int i = 0; i < et.size(); i++)
		pilaTurni.push_back(std::pair<std::shared_ptr<Entita>, cood>(et.at(i), po.at(i)));
	std::pair<std::shared_ptr<Entita>, cood> attivo;
	while (pilaTurni.size() != 0)
	{
		pregen.StampaChar();
		if (goAhead) {
			goAhead = false;
			attivo = pilaTurni.front();
			if (pregen.at(attivo.second).getEntita() == 0) { //

			}
			std::cout << "Adesso sta a " << attivo.first->getNome() << std::endl;
			pilaTurni.pop_front();
			if (pregen.getPositionOfPlayer() != attivo.second) {
				pregen.muoviEntita(attivo.second, pregen.getPositionOfPlayer());
				goPlayer = false;
				goAhead = true;
				attivo.second = pregen.getPositionOfEntity(attivo.first);
				pilaTurni.push_back(attivo);
			}
			else {
				goAhead = false;
				goPlayer = true;
				attivo.second = pregen.getPositionOfEntity(attivo.first);

			}

		}
		if (goPlayer) {
			if (a == 'y')
				std::cout << std::endl << "Usa il tastierino numerico per muoverti, 5 per uscire, 0 per guardare a terra,\np per raccogliere cio' che e' a terra, e per equipaggiare il primo oggetto nell'inventario nel posto dell'arma: ";
			char direzione;
			std::cin >> direzione;
			std::cout << std::endl;
			system("CLS");
			switch (direzione)
			{
			case '1': {
				auto result = pregen.muoviEntita(X, Y, X - 1, Y + 1);
				if (result == 0) {
					if (a == 'y')
						std::cout << "Ho provato a muovermi con successo." << std::endl;
					X--;
					Y++;
					attivo.second = cood(X, Y);
					pilaTurni.push_back(attivo);
					goAhead = true;
				}
				else if (result == 2)//TODO scontro deve restituire qualcosa
					pregen.scontro(cood(X - 1, Y + 1), cood(X, Y));

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
					attivo.second = cood(X, Y);
					pilaTurni.push_back(attivo);
					goAhead = true;
				}
				break;
			case '3':
				if (pregen.muoviEntita(X, Y, X + 1, Y + 1) == 0) {
					if (a == 'y')
						std::cout << "Ho provato a muovermi con successo." << std::endl;
					X++;
					Y++;
					attivo.second = cood(X, Y);
					pilaTurni.push_back(attivo);
					goAhead = true;
				}
				break;
			case '4':
				if (pregen.muoviEntita(X, Y, X - 1, Y) == 0) {
					if (a == 'y')
						std::cout << "Ho provato a muovermi con successo." << std::endl;
					X--;
					attivo.second = cood(X, Y);
					pilaTurni.push_back(attivo);
					goAhead = true;
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
					attivo.second = cood(X, Y);
					pilaTurni.push_back(attivo);
					goAhead = true;
				}
				break;
			case '7':
				if (pregen.muoviEntita(X, Y, X - 1, Y - 1) == 0) {
					if (a == 'y')
						std::cout << "Ho provato a muovermi con successo." << std::endl;
					X--;
					Y--;
					attivo.second = cood(X, Y);
					pilaTurni.push_back(attivo);
					goAhead = true;
				}
				break;
			case '8':
				if (pregen.muoviEntita(X, Y, X, Y - 1) == 0) {
					if (a == 'y')
						std::cout << "Ho provato a muovermi con successo." << std::endl;
					Y--;
					attivo.second = cood(X, Y);
					pilaTurni.push_back(attivo);
					goAhead = true;
				}
				break;
			case '9':
				if (pregen.muoviEntita(X, Y, X + 1, Y - 1) == 0) {
					if (a == 'y')
						std::cout << "Ho provato a muovermi con successo." << std::endl;
					X++;
					Y--;
					attivo.second = cood(X, Y);
					pilaTurni.push_back(attivo);
					goAhead = true;
				}
				break;
			case 'k':
				pregen.scontro(cood(31, 7), Danno(std::vector<double>{1}, 4000));
				break;
			case 'e':
				pregen.at(X, Y).getEntita()->equip(1, 0);
				attivo.second = cood(X, Y);
				pilaTurni.push_back(attivo);
				goAhead = true;
				break;
			case '0':
				std::cout << pregen.at(cood(X, Y)).descriviOggettiTerra();
				break;
			case 'p':
				pregen.at(cood(X, Y)).pickup();
				goAhead = true;
				attivo.second = cood(X, Y);
				pilaTurni.push_back(attivo);
				break;
			default:
				if (a == 'y')
				{
					std::cout << "Input non valido" << std::endl;
				}

			}
		}
	}

	pregen.StampaChar();
	pregen.muoviEntita(6, 2, X, Y); // muovo 2° entita

	pregen.StampaChar();
	std::cout << std::endl;
	std::cin >> a;

}