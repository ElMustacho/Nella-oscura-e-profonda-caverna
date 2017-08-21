#include <vector>
#include <iostream>
#include <memory>
#include <cstdlib>
#include <ctime>
#include "Entita.h"
#include "Danno.h"
Entita::~Entita()
{
	//TODO ~Entita()
}

Entita::Entita(std::string nome, std::list<std::shared_ptr<Oggetto>> inventario, Attributi attributi, std::vector<std::shared_ptr<Oggetto>> equipaggiamento): attributi(attributi) {
	
		this->nome = nome;
		this->equipaggiamento = equipaggiamento;
		this->inventario = inventario;
		this->attributi = attributi;
		this->equipaggiamento.reserve(20);
}
bool Entita::operator==(const Entita & rEntita) const
{
	if (typeid(this) == typeid(rEntita))
		if (this->nome == rEntita.nome)
			if (this->inventario == rEntita.inventario)
				if (this->equipaggiamento == rEntita.equipaggiamento)
					if (this->attributi == rEntita.attributi)
						return true;
	return false;
}
void Entita::muovi(int & distanza, int & metodoTrasporto)
{
	distanza = 1;
	//distanza = (int)(1+attributi.getDestrezza()/8); //distanza 0 significa essere immobili, ma chiamare questa funzione ed ottenere distanza 0 significa
				  //che si è provato a muoversi ma si è fallito (e il tentativo conta)
	metodoTrasporto = 0;
	// 0 = Camminare
	// 1 = Volare, atterraggio necessario (include saltare o lo vogliamo separare? //TODO)
	// 2 = Volare, ma fluttuare
	// 3 = Camminare + nuotare
	// 4 = Nuotare
	// 5 = Camminare + scavare
	// etc etc, quando ne avremo altri ne aggiungeremo
	// 100 = Teletrasporto

}


Danno Entita::attacca()
{
	if (equipaggiamento.size()==0)
		return Danno(std::vector<double>{1}, -1); //nulla in mano
	if (equipaggiamento.at(0).get()==nullptr)
		return Danno(std::vector<double>{1}, -1); //nulla in mano
	auto danno = equipaggiamento.at(0)->attacca();
	if (danno.getAmmontare() > 0) //is this even impossible
	{
		if (equipaggiamento.at(0)->getPeso() < 0.5) //arma piccola usa la destrezza
			danno.magnifica(attributi.getDestrezza() / 4);
		else										//arma grande no
			danno.magnifica(attributi.getForza() / 4);
		srand(time(nullptr));
		//FIXMe return sempre = 1
		double random = 1 - (((rand() % 6) / 12) - 1 / 6);
		danno.magnifica(random);
		return danno;
	}
	return Danno(std::vector<double>{1}, -1);
}

Entita::Entita()
{

}

Attributi Entita::getAttributi() const
{
	return attributi;
}


void Entita::setAttributi(Attributi attr)
{
	attributi = attr;
}
//FIXME per ora non gestisco tutti i casi.
bool Entita::addInventario(std::list<std::shared_ptr<Oggetto>> oggettiAggiunti)
{
	inventario.insert(inventario.end(), oggettiAggiunti.begin(), oggettiAggiunti.end());
	return true;
}

void Entita::equip(int posizioneFrom, int posiozioneTo) {
	if (posiozioneTo > 40) //troppo in là nell'inventario
		return;
	if (posizioneFrom<0 || posizioneFrom>inventario.size())
		return; //non è dentro
	else {
		auto it = inventario.begin();
		std::advance(it, posizioneFrom);
		auto moving = inventario;
		//HACK funziona solo con le armi
		equipaggiamento.push_back(*it);
		inventario.erase(it);
	}	//TODOFAR carico massimo
}

void Entita::unequip(int posisioneFrom) {
	if (posisioneFrom<0 || posisioneFrom>inventario.size())
		return; //non è dentro
	else {
		auto moving = equipaggiamento.at(posisioneFrom);
		equipaggiamento.push_back(moving);
		equipaggiamento.erase(equipaggiamento.begin() + posisioneFrom);
		return;
	}
}

bool Entita::addInventario(std::shared_ptr<Oggetto> oggettoDaAgginugere)
{
	inventario.push_back(oggettoDaAgginugere);
	return true;
	//CHECK posso fallire, cosa potrebbe andare male?
}
//return true se uccide, false altrimenti
bool Entita::subisciDanno(Danno dannoSubito)
{
	double totalehp = 0;
	//LOOKATME potremmo per esempio lasciare che alcuni tipi di danno abbiano altri effetti, tipo il danno mentale infligge danni alla barra delle magia
	for (unsigned int i = 0; i < Danno::giveCategoriaDanni().size();i++)
	{
		totalehp += attributi.getResistenze()[i] * dannoSubito.getParteDanno(i);
	}
	attributi.setHp((int)(attributi.getHp()-totalehp));
	if (attributi.getHp() < 0) { //dead
		onDeath();
		return true;
	}
	std::cout << nome << " ha sofferto " << totalehp << " danni!" << std::endl;
	return false;
}


double Entita::carryWeight()
{ //Calcola il carico trasportato
	double total = 0;
	for (auto i : inventario) 
	{
		total += i->getPeso();
	}
	for (auto i : equipaggiamento) 
	{
		total += i->getPeso() / 2;	// Gli oggetti equipaggiati vengono calcolati con un peso minore perché in quanto
	}								// più vicini al centro di massa (l'entità che li solleva) serve meno sforzo per
	return total;					// sollevarli.
}


void Entita::onDeath()
{
	auto peso = attributi.getForza() * 10 + attributi.getTempra() * 10 + attributi.getDestrezza() * 2 + attributi.getIntelligenza()*0.25; //L'intelligenza significa la dimensione del cervello. L'intelligenza non dipende dalla quantità di cervello nel mondo reale (dipende dalle sinapsi), ma questo è un gioco.
	auto object = std::make_shared<Oggetto>(Oggetto(peso, "Cadavere di" + nome, "La carcassa di " + nome + " oramai esanime.", 0));
	addInventario(object);
	std::cout << nome << " e' morto!" << std::endl; //TODOFAR implementa sesso
}
std::string Entita::describeInventario() {
	std::string returnStringa;
	for (auto i = inventario.begin(); i != inventario.end(); i++)
		returnStringa.append(i->get()->getDescrizione());
	return returnStringa;
}
