#include "Casella.h"
#include "Scrigno.h"
#include <iostream>
#include <algorithm>
#include <ctime>
#include <random>
Casella::Casella(std::list<std::shared_ptr<Oggetto>> oggetti, std::shared_ptr<Entita> entita, bool trasparenza, bool attraversabile, int evento, int x, int y)
{
	this->oggetti = oggetti;
	this->entita = entita;
	this->trasparenza = trasparenza;
	this->attraversabile = attraversabile;
	this->evento = evento;
	if (x < 0)
		x = 0;
	else
	xTexture = x;
	if (y < 0)
		y = 0;
	else
	yTexture = y;
	maxxTexture = 1;
	maxyTexture = 1;
}

//Costruttore rapido e semplice, passare false per parete, passare true per terreno attraversabile
Casella::Casella(bool default) {
	srand((unsigned int)time(nullptr));
	trasparenza = default; //Se è una parete non è trasparente
	attraversabile = default; //Se è una parete non è attraversabile
	evento = 0; //Di default non accade nulla
	xTexture = 0;
	yTexture = 0;
	maxxTexture = 1;
	maxyTexture = 1;
	xTexture = 0;
	yTexture = 0;
}

bool Casella::isMuro()
{
	if (!attraversabile)
		if(!trasparenza)
			return true;
	return false;
}

	
void Casella::chooseTile()
{
	//LOOKATME sono un gigantilione di volte migliore di srand(time(nullptr))

	std::random_device rd;
	std::mt19937 mt(rd());

	//sceglie tra una possibile variante della stessa categoria di casella.
	std::uniform_real_distribution<double> dist(0., (double)maxxTexture / 32);
	xTexture =(int) dist(mt); 

	//Decide la categoria di casella, ad esempio parete, pavimento, corridoio etc.
	//Per ora c'è solo muro on non muro (questo è il dilemma) cit.
	if (isMuro())
		yTexture = 0;
	else
		yTexture = 1;
}

sf::IntRect Casella::getRectSprite() const
{
	return sf::IntRect(xTexture*32,yTexture*32,xTexture*32+32,yTexture*32+32);
}
//Cancella tutto e ripopola con quelli dati
void Casella::setOggetti(std::list<std::shared_ptr<Oggetto>> oggetti) 
{
	this->oggetti = oggetti;
}
//Raccoglie tutto quanto
void Casella::pickup() {
	if (entita != nullptr) {
		std::list<std::shared_ptr<Oggetto>> moving;
		moving.splice(moving.end(), oggetti);
		entita->addInventario(moving);
		chooseTile();
	}
}
//TODO raccoglie solo qualche oggetto
void Casella::pickup(std::vector<unsigned int> posizioni) {
	chooseTile();
}
//Drop all
void Casella::drop()
{
	for each (std::shared_ptr<Oggetto> oggettoMoving in entita->getInventario())
	{
		oggetti.push_back(oggettoMoving);
	}
	entita->getInventario().clear();
	chooseTile();
}


std::string Casella::descriviOggettiTerra()
{
	std::string output="";
	for each (auto oggetto in oggetti)
	{
		output.append(oggetto->getNome() + "\n");
	}
	return output;
}

void Casella::addOggetto(std::shared_ptr<Oggetto> oggetto) {
	oggetti.push_back(oggetto);
	chooseTile();
}
//TODO
void Casella::addOggetti(std::vector<std::shared_ptr<Oggetto>> oggetti)
{
	for each (auto obj in oggetti)
	{
		this->oggetti.push_back(obj);
	}
	chooseTile();
}

bool Casella::setEntita(std::shared_ptr<Entita> entity) //TODO gestire la sovrapposizione delle entità, avremo memory leak se cancelliamo la precedente!
{
	if (this->isMuro()) //Quando avremo entità incorporee questo if dovrà essere alterato
		return false;
	this->entita = entity;
	chooseTile();
	return true;
}

int Casella::doEvento()//FIXME sono un segnaposto
{
	if (evento == 1 && dynamic_cast<Protagonista*>((&entita)->get())!=nullptr) {
		std::cout << "Vuoi salire sulle scale(y/n): ";
		char input='4';
		while (input != 'y'&&input != 'n')
			std::cin >> input;
		if (input == 'y')
			return 100;
		else
			return 0;
	}
	//FIXME beh per ora l'unico evento sono le scale ma immagino che ci sarà una lunga fila di case in uno switch
	return 0;
}

Casella::~Casella() //Se non libero questi puntatori non lo farà nessuno, PERÒ nessuno mi garantisce che io non preservi
					//cose importanti
{
	//delete (oggetto);
	//delete (entita);
}

void Casella::Scava() { //per scavare un muro in modo rapido
	trasparenza = true; //Da muro a pavimento
	attraversabile = true;
	chooseTile();
}

bool Casella::hasTrap()
{
	return false; // TODO Cambiare: dovrà provare un castin a Trappola
}