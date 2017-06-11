#include <iostream>
#include "Oggetto.h"
#include "Entit�.h"

int main() 
{
	Entit� player1("Pippo",Attributi()); 
	std::cout << "Giocatore: " << player1.getNome() << std::endl;

int main() {
	Oggetto idolo(15., "Hatkanda", "L'oggetto di un film generico", 400); 
	std::cout << idolo.getDescrizione() << std::endl << idolo.getNome() << std::endl << idolo.getPeso() << std::endl <<
		idolo.getValore();
	char a;
	std::cout << std::endl;
	std::cin >> a;
  //Questo main dovrà finire in un test.
}