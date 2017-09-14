#pragma once
#include <memory>
#include "Oggetto.h"
#include "Entita.h"
#include "Texture.h"
#include "Protagonista.h"
class Casella
{

public:
	Casella(std::list<std::shared_ptr<Oggetto>> oggetti, std::shared_ptr<Entita> entita, bool trasparenza, bool attraversabile, int evento, std::string pathToFile="", int x = -1, int y = -1); //CHECK quando vuoi dare valori di default, devono essere messi nel .cpp, non nel .h, altrimenti è un casino!
	~Casella();
	void Scava();
	Casella(bool default, std::string pathToFile=""); //Default
	bool isMuro();
	void setTrasparenza(bool trasparenza) { this->trasparenza = trasparenza; }
	bool isTrasparente() { return this->trasparenza; }
	void setAttraversabile(bool attraversabile) { this->attraversabile = attraversabile; }
	bool isAttraversabile() { return this->attraversabile; }
	void chooseTile();
	std::list<std::shared_ptr<Oggetto>> getOggetti() { return this->oggetti; }
	std::shared_ptr<Entita> getEntita() { return this->entita; }
	sf::IntRect getRectSprite() const;
	void setOggetti(std::list<std::shared_ptr<Oggetto>> oggetti);
	void pickup();
	void pickup(std::vector<unsigned int> posizioni);
	void drop();
	std::string descriviOggettiTerra();
	void addOggetto(std::shared_ptr<Oggetto> oggetto);
	void addOggetti(std::vector<std::shared_ptr<Oggetto>> oggetti);
	bool setEntita(std::shared_ptr<Entita> entita);
	void setEvento(int evento) { this->evento = evento; };
	int getEvento() const { return evento; };
	int doEvento();
	bool hasTrap();
	int getxTexture()const { return xTexture; };
	int getyTexture()const { return yTexture; };
	void setxTexture(int xTexture) { this->xTexture = xTexture; };
	void setyTexture(int yTexture) { this->yTexture = yTexture; };
	std::string getPathToFile()const { return pathToTile; };
private:
	std::string pathToTile;
	std::list<std::shared_ptr<Oggetto>> oggetti;
	std::shared_ptr<Entita> entita;
	bool trasparenza;
	bool attraversabile;
	int evento;
	int xTexture, yTexture, maxxTexture, maxyTexture;
};

