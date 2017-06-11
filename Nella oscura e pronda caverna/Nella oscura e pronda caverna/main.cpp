#include<iostream>
#include"Oggetto.h"

int main() {
	Oggetto idolo(15., "Hatkanda", "L'oggetto di un film generico", 400); //CHECK
	std::cout << idolo.getDescrizione() << std::endl << idolo.getNome() << std::endl << idolo.getPeso() << std::endl <<
		idolo.getValore();
	//idolo.~Oggetto();
	char a;
	std::cout << std::endl;
	std::cin >> a;
}