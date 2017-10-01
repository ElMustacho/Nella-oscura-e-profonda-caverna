#include "DisplayStatoProtagonista.h"



DisplayStatoProtagonista::DisplayStatoProtagonista(Observee* stato) : statoProtagonista(stato)
{
	livello = 0;
	esperienza = 0;
	fondiEconomici = 0;
	nome = "";
	attributi = Attributi();
	inventario = std::vector<std::shared_ptr<Oggetto>>();
	equipaggiamento = Equipaggiamento();
	statoProtagonista->registerObserver(this);
}


DisplayStatoProtagonista::~DisplayStatoProtagonista()
{
	statoProtagonista->removeObserver(this);
}

void DisplayStatoProtagonista::update(unsigned int lv, double exp, long int money, std::string name, Attributi attr, std::vector<std::shared_ptr<Oggetto>> inventory, Equipaggiamento equip)
{
	livello = lv;
	esperienza = exp;
	fondiEconomici = money;
	nome = name;
	attributi = attr;
	inventario = inventory;
	equipaggiamento = equip;
	display();
}

void DisplayStatoProtagonista::display() const
{
	//TODO crea finestra che visualizzi lo stato del protagonista

	std::cout << "Stato " << nome << "::" << std::endl;
	std::cout << "Livello: " << livello << std::endl;
	std::cout << "Esperienza: " << esperienza << std::endl;
	std::cout << "Soldi: " << fondiEconomici << std::endl;
}