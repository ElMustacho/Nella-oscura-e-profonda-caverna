#include <vector>
#include "Entita.h"
#include <memory>

Entita::~Entita()
{
	//TODO ~Entita()
}

Entita::Entita(std::string nome, std::list<std::shared_ptr<Oggetto>> inventario, Attributi attributi, std::vector<std::shared_ptr<Oggetto>> equipaggiamento): attributi(attributi) {
	
		this->nome = nome;
		this->equipaggiamento = equipaggiamento;
		this->inventario = inventario;
		this->attributi = attributi;
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

bool Entita::addInventario(std::shared_ptr<Oggetto> oggettoDaAgginugere)
{
	inventario.push_back(oggettoDaAgginugere);
	return true;
	//CHECK posso fallire, cosa potrebbe andare male?
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

}
std::string Entita::describeInventario() {
	std::string returnStringa;
	for (auto i = inventario.begin(); i != inventario.end(); i++)
		returnStringa.append(i->get()->getDescrizione());
	return returnStringa;
}
