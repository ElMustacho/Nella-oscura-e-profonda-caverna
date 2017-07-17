#include <iostream>
#include <ctime>
#include "Oggetto.h"
#include "Entita.h"
#include "Piano.h"
int main() 
{
	//Entita player1("Pippo",Attributi()); // Il costruttore vuoto di Attributi non deve esistere
	//std::cout << "Giocatore: " << player1.getNome() << std::endl;

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
	// TODO add objects on the map

	int exit = 0;
	int X = 5, Y = 5;
	std::cout << std::endl;

	while (exit == 0) 
	{
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
  //Questo main dovrà finire in un test.
}