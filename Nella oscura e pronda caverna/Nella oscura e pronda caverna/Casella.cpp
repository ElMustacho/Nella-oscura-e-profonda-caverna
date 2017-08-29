#include "Casella.h"
#include "Scrigno.h"
#include <iostream>
#include <cstdlib>
#include <algorithm>
Casella::Casella(Tileset tileset, std::list<std::shared_ptr<Oggetto>> oggetti, std::shared_ptr<Entita> entita, bool trasparenza, bool attraversabile, int evento)
{
	this->tileset = tileset;
	this->oggetti = oggetti;
	this->entita = entita;
	this->trasparenza = trasparenza;
	this->attraversabile = attraversabile;
	this->evento = evento;
}

//Costruttore rapido e semplice, passare false per parete, passare true per terreno attraversabile
Casella::Casella(bool default) {
	tileset = Tileset(); //FIX ME quando Tileset avrà senso questo dovrà essere qualcosa di concreto.
	trasparenza = default; //Se è una parete non è trasparente
	attraversabile = default; //Se è una parete non è attraversabile
	evento = 0; //Di default non accade nulla
}

bool Casella::isMuro()
{
	if (!attraversabile)
		if(!trasparenza)
			return true;
	return false;
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
	}
}
//TODO raccoglie solo qualche oggetto
void Casella::pickup(std::vector<unsigned int> posizioni) {

}

void Casella::drop()
{
	for each (std::shared_ptr<Oggetto> oggettoMoving in entita->getInventario())
	{
		oggetti.push_back(oggettoMoving);
	}
	entita->getInventario().clear();
}
//TODO abbandona solo quanche oggetto
void Casella::drop(std::vector<unsigned int> posizioni)
{
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
}
//TODO
void Casella::addOggetti(std::vector<std::shared_ptr<Oggetto>> oggetti)
{
}

bool Casella::setEntita(std::shared_ptr<Entita> entity) //TODO gestire la sovrapposizione delle entità, avremo memory leak se cancelliamo la precedente!
{
	if (this->isMuro()) //Quando avremo entità incorporee questo if dovrà essere alterato
		return false;
	this->entita = entity;
	return true;
}

int Casella::doEvento()//FIXME sono un segnaposto
{
	if (evento == 1 && dynamic_cast<Protagonista*>((&entita)->get())!=nullptr) {
		std::cout << "Hai vinto!";
		char a;
		std::cin >> a;
		exit(EXIT_SUCCESS);
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
	tileset = Tileset(); //Da muro a pavimento
	trasparenza = true;
	attraversabile = true;
}

bool Casella::hasTrap()
{
	return false; // TODO Cambiare: dovrà provare un castin a Trappola
}