#pragma once
#include "Arma.h"
#include "Armatura.h"
#include <memory>
class Equipaggiamento
{
public:
	Equipaggiamento();
	~Equipaggiamento();
	bool equipaggia(std::shared_ptr<Oggetto> toEquip);
	void setArmaPrimaria(std::shared_ptr<Arma> armaPrimaria) { this->armaPrimaria = armaPrimaria; };
	std::shared_ptr<Arma> getArmaPrimaria() const { return armaPrimaria; };
	void setArmatura(std::shared_ptr<Armatura> armatura) { this->armatura = armatura; };
	std::shared_ptr<Armatura> getArmatura() const { return armatura; };
	//vedi Equipaggiamento.h per capire a cosa posizione punterà
	std::shared_ptr<Oggetto> disequip(int posizione);
private:
	std::shared_ptr<Arma> armaPrimaria;
	std::shared_ptr<Armatura> armatura;
};


/*
per disequipaggiare
0) mano primaria (arma)
1) mano secondaria (arma, arma2 o scudo)
2) torso
3) gambali
4) guanti
5) bracciali
6) stivali
7) elmo
8) collana
9) cintura
10) fascia
11) anello 1
12) anello 2
13) spazio munizioni
14) abiti
15) mantello
16) da qui in poi potranno esserci elementi che non si cumulano con i suddetti, come per esempio aureole,
maledizioni, benedizioni e simili.
*/