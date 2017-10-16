#include "Protagonista.h"
#include <memory>
#include <iostream>


Protagonista::Protagonista(std::string nome, std::vector<std::shared_ptr<Oggetto>> inventario, Attributi attributi, Equipaggiamento equipaggiamento, unsigned int livello, double esperienza, long int fondiEconomici, std::string posTofile) : Entita(nome, inventario, attributi, equipaggiamento, posTofile)
{
	this->livello = livello;
	this->esperienza = esperienza;
	this->fondiEconomici = fondiEconomici;
	regenerationMemory = 0;
}

void Protagonista::updateLevel() {
	Observer* shm = (Observer*)graphic;
	shm->updateLevel(livello);
}

void Protagonista::update()
{
	auto attr = getAttributi();
	Observer* shm = (Observer*)graphic;
	auto n1 = (double)(attr.getHp() / (double)attr.getMaxHp());
	auto n2 = (double)(attr.getStamina() / (double)attr.getMaxStamina());
	auto n3 = (double)(attr.getPotereMagico() / (double)attr.getMaxPotereMagico());
	shm->update(n1,n2,n3);
}



Protagonista::~Protagonista()
{
}

bool Protagonista::subisciDanno(Danno dannoSubito, TextBox & messages)
{
	double totalehp = 0;
	//LOOKATME potremmo per esempio lasciare che alcuni tipi di danno abbiano altri effetti, tipo il danno mentale infligge danni alla barra delle magia
	for (unsigned int i = 0; i < Danno::giveCategoriaDanni().size(); i++)
	{
		totalehp += attributi.getResistenze()[i] * dannoSubito.getParteDanno(i);
	}
	
	if (totalehp <= 0) {
		std::cout << "Sei rimasto incolume!" << std::endl;
		messages.text.setString(messages.text.getString() +"Sei rimasto incolume! \n");
		return false;
	}
	attributi.setHp((int)(attributi.getHp() - totalehp));
	update();
	if (attributi.getHp() < 0) { //dead
		onDeath(messages);
		return true;
	}
	std::cout<< "Hai sofferto " << (int)totalehp << " danni!" << std::endl;
	messages.text.setString(messages.text.getString() +"Hai sofferto " + std::to_string((int)totalehp) + " danni!\n");
	return false;
}

void Protagonista::onDeath(TextBox& messages)
{
	/*std::cout << "Sei orribilmente morto." << std::endl;
	messages.text.setString("Sei orribilmente morto.\n");
	char a;
	std::cin >> a;
	exit(EXIT_SUCCESS);*/
}

void Protagonista::attachGraphic(Observer* obs)
{
	graphic = obs;
	update();
	//CHECK Test to make red rect when after the stairs
	updateLevel();
}

void Protagonista::regeneration()
{
	auto baseRegen = (double)getAttributi().getTempra() / (double)7;
	regenerationMemory += baseRegen;
	if (regenerationMemory < 1) {
		return;
	}
	else {
		attributi.setHp(attributi.getHp() + (int)regenerationMemory);
		regenerationMemory -= (int)regenerationMemory;
		update();
	}
}

void Protagonista::guadagnaEsperienza(double experienceGain)
{
	esperienza += experienceGain;
	if (esperienza > livello * 40) {
		esperienza = 0;
		livello++;
		updateLevel();
	}
}
