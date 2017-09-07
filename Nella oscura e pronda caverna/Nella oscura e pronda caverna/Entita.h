#pragma once
#include <string>
#include <vector>
#include <list>
#include <memory>
#include "Oggetto.h"
#include "Attributi.h"
#include "Equipaggiamento.h"

class Entita
{

public:


	virtual ~Entita();
	std::string getNome() const { return nome; }

	void setNome(std::string nome) { this->nome = nome; }
	virtual void onDeath(); //cosa succede se muore
	std::list<std::shared_ptr<Oggetto>> getInventario() const { return inventario; };
	void setInventario(std::list<std::shared_ptr<Oggetto>> inventario) { this->inventario = inventario; };
	std::vector<std::shared_ptr<Oggetto>> getEquipaggiamento() const { return equipaggiamento; };
	void setEquipaggiamento(std::vector<std::shared_ptr<Oggetto>> equipaggiamento) { this->equipaggiamento = equipaggiamento; }
	Entita(std::string nome, std::list<std::shared_ptr<Oggetto>> inventario, Attributi attributi, std::vector<std::shared_ptr<Oggetto>> equipaggiamento);
	bool operator==(const Entita & rEntita)const;
	void muovi(int &distanza, int &metodoTrasporto);
	Danno attacca();
	Entita(); //TODO vorrei evitare di mettere costruttori vuoti solo perché se no il compilatore si lamenta.
	Attributi getAttributi() const;
	void setAttributi(Attributi attr);
	bool addInventario(std::list<std::shared_ptr<Oggetto>> oggettiAggiunti);
	void equip(int posizioneFrom, int posizioneTo);
	void unequip(int posisioneFrom);
	bool addInventario(std::shared_ptr<Oggetto> oggettoDaAgginugere);
	//return true se uccide, false altrimenti
	bool subisciDanno(Danno dannoSubito);
	double carryWeight(); //calcolo peso trasportato
	std::string describeInventario();
private:
	std::string nome;
	Attributi attributi;
	//FIXME Sprite sprite;   manage Sprite
	std::list<std::shared_ptr<Oggetto>> inventario;
	//LOOKATME i vector si shrinkano automaticamente quindi direi che in futuro equipaggiamento sarà una classe a sé stante
	std::vector<std::shared_ptr<Oggetto>> equipaggiamento;
	Equipaggiamento equipaggiamentoNext;
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
