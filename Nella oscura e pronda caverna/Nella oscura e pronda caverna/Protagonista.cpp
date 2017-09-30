#include "Protagonista.h"
#include <memory>
#include <iostream>


Protagonista::Protagonista(std::string nome, std::vector<std::shared_ptr<Oggetto>> inventario, Attributi attributi, Equipaggiamento equipaggiamento, unsigned int livello, double esperienza, long int fondiEconomici, std::string posTofile) : Entita(nome, inventario, attributi, equipaggiamento, posTofile)

{
	this->livello = livello;
	this->esperienza = esperienza;
	this->fondiEconomici = fondiEconomici;
}


Protagonista::~Protagonista()
{
}

void Protagonista::onDeath(TextBox& messages)
{
	/*std::cout << "Sei orribilmente morto." << std::endl;
	messages.text.setString("Sei orribilmente morto.\n");
	char a;
	std::cin >> a;
	exit(EXIT_SUCCESS);*/
}
