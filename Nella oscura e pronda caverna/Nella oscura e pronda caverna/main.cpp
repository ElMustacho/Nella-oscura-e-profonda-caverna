#include <iostream>
#include "Oggetto.h"
#include "Entità.h"

int main() 
{
	Entità player1("Pippo",Attributi());
	std::cout << "Giocatore: " << player1.getNome() << std::endl;
	player1.~Entità();

	Oggetto idolo((double)15,"Hatkanda","L'oggetto di un film generico",(long) 400);
	std::cout << idolo.getDescrizione() << std::endl << idolo.getNome() << std::endl << idolo.getPeso() << std::endl <<
		idolo.getValore() << std::endl;
	idolo.~Oggetto();
	int a;
	std::cin >> a;
}