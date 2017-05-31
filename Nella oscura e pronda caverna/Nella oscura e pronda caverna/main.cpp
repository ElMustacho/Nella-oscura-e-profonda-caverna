#include<iostream>
#include"Oggetto.h"

int main() 
{
	Oggetto idolo((double)15,"Hatkanda","L'oggetto di un film generico",(long) 400);
	std::cout << idolo.getDescrizione() << std::endl << idolo.getNome() << std::endl << idolo.getPeso() << std::endl <<
		idolo.getValore();
	idolo.~Oggetto();
	int a;
	std::cin >> a;
}