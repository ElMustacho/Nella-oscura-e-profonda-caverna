#include <iostream>
#include "Oggetto.h"
#include "Entita.h"

int main() 
{
	Entita player1("Pippo", Attributi(1, 2, 3, 4, 5, 6, 7, 8)); 
	std::cout << "Giocatore: " << player1.getNome() << std::endl;

	Oggetto idolo(15., "Hatkanda", "L'oggetto di un film generico", 400); 
	std::cout << idolo.getDescrizione() << std::endl << idolo.getNome() << std::endl << idolo.getPeso() << std::endl <<
		idolo.getValore();
	char a;
	std::cout << std::endl;
	std::cin >> a;
  //Questo main dovrà finire in un test.
}