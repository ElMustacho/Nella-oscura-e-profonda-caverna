#include <vector>
#include "Entita.h"




Entita::Entita(std::string nome, std::vector<Oggetto> inventario, Attributi attributi, std::vector<Oggetto> equipaggiamento): attributi(attributi) {
	
		this->nome = nome;
		this->equipaggiamento = equipaggiamento;
		this->inventario = inventario;
		this->attributi = attributi;
}

void Entita::muovi(int & distanza, int & metodoTrasporto)
{
	distanza = 1; //distanza 0 significa essere immobili, ma chiamare questa funzione ed ottenere distanza 0 significa
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

/*Entita::Entita()
{

}*/





Entita::~Entita()
{
	//TODO
}

double Entita::carryWeight()
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
