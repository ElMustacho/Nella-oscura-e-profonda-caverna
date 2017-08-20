#pragma once
#include <string>
#include <vector>
#include <list>
#include "Oggetto.h"
#include "Sprite.h"
#include "Attributi.h"
#include <memory>

class Entita
{

public:

	
	virtual ~Entita();
	std::string getNome() const
	{
		return nome;
	}

	void setNome(std::string nome)
	{
		this->nome = nome;
	}

	void onDeath(); //cosa succede se muore

	Entita(std::string nome, std::list<std::shared_ptr<Oggetto>> inventario, Attributi attributi, std::vector<std::shared_ptr<Oggetto>> equipaggiamento);

	bool operator==(const Entita & rEntita)const;

	void muovi(int &distanza, int &metodoTrasporto);

	// TODO implement method raccogli
	// TODO implement method combatti/colpisci

	Entita(); //TODO vorrei evitare di mettere costruttori vuoti solo perché se no il compilatore si lamenta.
	Attributi getAttributi() const;
	void setAttributi(Attributi attr);
	bool addInventario(std::list<std::shared_ptr<Oggetto>> oggettiAggiunti);
	bool addInventario(std::shared_ptr<Oggetto> oggettoDaAgginugere);
	//return true se uccide, false altrimenti
	bool subisciDanno(Danno dannoSubito);
	double carryWeight(); //calcolo peso trasportato
	std::string describeInventario();
private:
	std::string nome;
	Attributi attributi;
	//FIXME Sprite sprite;   manage Sprite
	std::list<std::shared_ptr<Oggetto>> inventario; //CHECK forse è meglio che sia una lista, così posso gestire meglio i buchi nell'inventario (di fatto eliminandoli)
	std::vector<std::shared_ptr<Oggetto>> equipaggiamento;
	/*
	nella posizione X di equipaggiamento ci sarà:
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
};
