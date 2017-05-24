#pragma once
#include <string>
#include <vector>
#include "Oggetto.h"
#include "Attributi.h"
class Entità
{
public:
	Entità();
	~Entità();

private:
	std::string nome;
	Attributi attributi;
	std::vector<Oggetto> inventario;
	std::vector<Oggetto> equipaggiamento;
	/*
	nella posizione X di equipaggiamento ci sarà:
	0) mano destra (arma)
	1) mano sinistra (arma, arma2 o scudo)
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

	*/
};

