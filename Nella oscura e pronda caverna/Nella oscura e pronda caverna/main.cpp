#include <iostream>
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
	char a;
	std::cout << std::endl;
	std::cin >> a;
	std::vector<Oggetto> tabellaLoot; //VUOTA
	std::vector<Entita> tabellaEntita; //VUOTA
	Protagonista Saitama("Saitama",tabellaLoot,Attributi(),tabellaLoot,1,0.,0); //Sto usando tabella loot giusto perchè è vuota
	Piano primoLivello(10,8,1,tabellaLoot,tabellaEntita);
	auto s = primoLivello.creaStanzaRettangolare(4, 4, 3, 2);
	
	if (!primoLivello.at(5, 5).setEntita(&Saitama)) {
		std::cout << "Fallito" << std::endl;
	}

	primoLivello.StampaChar();
	std::cout << std::endl;
	std::cin >> a;
  //Questo main dovrà finire in un test.
}