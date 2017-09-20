#pragma once
#include <string>
#include <vector>
#include <list>
#include <memory>
#include "Oggetto.h"
#include "Attributi.h"
#include "Equipaggiamento.h"
#include "TextBox.h"

class Entita
{

public:


	virtual ~Entita();
	std::string getNome() const { return nome; }
	std::string getPathToTile() const { return pathToTile; }
	void setNome(std::string nome) { this->nome = nome; }
	void setPathToTile(std::string pathToTile) { this->pathToTile = pathToTile; }

	virtual void onDeath(TextBox& messages); //cosa succede se muore
	std::vector<std::shared_ptr<Oggetto>> getInventario() const { return inventario; };
	void setInventario(std::vector<std::shared_ptr<Oggetto>> inventario) { this->inventario = inventario; };
	Equipaggiamento getEquipaggiamento() const { return equipaggiamento; };
	void setEquipaggiamento(Equipaggiamento equipaggiamento) { this->equipaggiamento = equipaggiamento; }
	Entita(std::string nome, std::vector<std::shared_ptr<Oggetto>> inventario, Attributi attributi, Equipaggiamento equipaggiamento, std::string pathToFile = "");
	bool operator==(const Entita & rEntita)const;
	void muovi(int &distanza, int &metodoTrasporto);
	Danno attacca();
	Entita(); //TODO vorrei evitare di mettere costruttori vuoti solo perché se no il compilatore si lamenta.
	Attributi getAttributi() const;
	void setAttributi(Attributi attr);
	bool addInventario(std::list<std::shared_ptr<Oggetto>> oggettiAggiunti);
	bool equip(int posizioneOggetto);
	bool equip(sf::RenderWindow& window,TextBox& messages);
	bool addInventario(std::shared_ptr<Oggetto> oggettoDaAgginugere);
	//return true se uccide, false altrimenti
	bool subisciDanno(Danno dannoSubito, TextBox& messages);
	double carryWeight(); //calcolo peso trasportato
	std::string describeInventario();
	
private:
	//TODO finish this
	std::string pathToTile;
	std::string nome;
	Attributi attributi;
	std::vector<std::shared_ptr<Oggetto>> inventario;
	Equipaggiamento equipaggiamento;
};
