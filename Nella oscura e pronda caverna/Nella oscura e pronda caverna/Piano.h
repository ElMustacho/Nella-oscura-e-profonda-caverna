#pragma once
#include <vector>
#include <deque>
#include "MonsterFactory.h"
#include "ObjectFactory.h"
#include "Casella.h"
#include "Entita.h"
#include "Oggetto.h"
#include "Protagonista.h"
#include "Attore.h"
#include "Arma.h"
#include "TextBox.h"

/*
LOOKATME
Che sia chiaro una volta per tutte, anche perché io mi sbaglio più o meno sempre, dannato sia il 2D

l larghezza ---> X
u ##################
n ##################
g ########........##
h ########........##
e ########........##
z #############.####
z #############.####
a #############.####
| #############.####
| ###..............#
| ###..............#
V ###..............#
  ###..............#
Y ##################
*/

typedef std::pair<int, int> coord;

struct node
{
	node() {}
	node(int posX, int posY, int parentX, int parentY, double f, double g, double h)
	{
		this->posX = posX;
		this->posY = posY;

		this->parentX = parentX;
		this->parentY = parentY;

		this->f = f; // movement cost + heuristic 
		this->g = g; // movement cost
		this->h = h; // heuristic
	}
	int posX, posY;
	int parentX, parentY;
	double f, g, h;
};

class Piano
{
public:
	virtual ~Piano();

	int posizione(int x, int y);

	bool removeEntita(coord coodElimina);
	int scontro(coord posizioneVittima, coord posizioneAttaccante, TextBox& messages);
	int scontro(coord posizioneVittima, coord posizioneAttaccante);
	int scontro(coord posizioneVittima, Danno dannoInflitto, TextBox& messages); //gestisce danno ad area e fulmini da divinità furiose

	int scontro(coord posizioneVittima, Danno dannoInflitto);

	Casella& at(int x, int y);
	Casella& at(coord coord);
	bool isCoodLegal(coord coord);
	int posizione(coord coord);
	coord fromPosizioneToInt(int x);
	bool creaStanzaRettangolare(int posX, int posY, int dimX, int dimY);
	bool creaPorte(int posX, int posY, int dimX, int dimY);
	std::vector<std::shared_ptr<Entita>> getVectorEntita();
	std::vector<coord> getVectorPosizioni();
	std::vector<coord> floodFill(coord posizionePartenza);
	void StampaChar();
	bool getLoquace()const { return loquace; };
	void setLoquace(bool loquace) { this->loquace = loquace; };
	coord getPositionOfPlayer();
	//posizione nella tabella
	coord getPositionOfEntity(std::shared_ptr<Entita> entita);
	int muoviEntita(int posX, int posY, int targetX, int targetY);

	int muoviEntita(coord pos, coord target);
	void checkSuccessor(coord check, coord target, std::string direct, bool &destination, node &q, std::vector<node> &openList, std::vector<node> &closedList);
	int aStar(coord pos, coord target, int distanza, int metodo);
	int playPiano(sf::RenderWindow& window, TextBox& messages);
	int playerAct(sf::RenderWindow& window, TextBox& messages);
	void StampaFileChar();
	bool popolaPiano();
	bool rSpargiLoot();
	bool placeEntita(std::shared_ptr<Entita> placeMe, coord coord);
	Piano();
	Piano(int larghezza, int lunghezza, std::vector<std::shared_ptr<Oggetto>> lootPossibile, std::vector<std::shared_ptr<Entita>> entitaPossibili);
	//TODOFAR far funzionare con entita generabili
	std::shared_ptr<Entita> entityFactory(std::string nome);
	std::shared_ptr<Entita> entityFactory(int codiceID = 0);
	std::shared_ptr<Oggetto> objectFactory(std::string nome);
	std::shared_ptr<Oggetto> objectFactory(int codiceID = 0);

	

	//Piano(std::string posizione, bool &successo); //Da file 
protected:
	bool loquace;
	std::vector<Casella> pavimento;
	int lunghezza, larghezza;
	std::vector<std::shared_ptr<Entita>> entitaGenerabili;
	std::vector<std::shared_ptr<Oggetto>> oggettiGenerabili;
	MonsterFactory monFact;
	ObjectFactory objFact;
	//Il personaggio deve essere sempre nella prima posizione
	std::vector<std::pair<std::shared_ptr<Entita>, coord>> entitaPresenti;
	std::string pathToFile;
	std::deque<Entita> turni;
	int maxxTexture, maxyTexture;
};
