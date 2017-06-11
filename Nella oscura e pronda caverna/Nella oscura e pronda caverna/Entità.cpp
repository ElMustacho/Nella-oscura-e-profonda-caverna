#include <vector>
#include "Entità.h"


Entità::Entità(std::string nome, std::vector<Oggetto> inventario, Attributi attributi, std::vector<Oggetto> equipaggiamento): attributi(attributi) {
	
		this->nome = nome;
		this->equipaggiamento = equipaggiamento;
		this->inventario = inventario;
}



Entità::~Entità()
{
	//TODO
}

double Entità::carryWeight()
{ //Calcola il carico trasportato
	double total = 0;
	for (auto i : inventario) {
		total += i.getPeso();
	}
	for (auto i : equipaggiamento) {
		total += i.getPeso() / 2;	// Gli oggetti equipaggiati vengono calcolati con un peso minore perché in quanto
	}								// più vicini al centro di massa (l'entità che li solleva) serve meno sforzo per
	return total;					// sollevarli.
}
