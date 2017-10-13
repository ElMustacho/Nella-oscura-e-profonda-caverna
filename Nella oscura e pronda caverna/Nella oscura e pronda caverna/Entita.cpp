#include <vector>
#include <iostream>
#include <memory>
#include <cstdlib>
#include <ctime>

#include "Entita.h"
#include "Danno.h"
#include "TextBox.h"
#include "UtilityGrafica.h"

Entita::~Entita()
{
	//TODO ~Entita()
}

Entita::Entita(std::string nome, std::vector<std::shared_ptr<Oggetto>> inventario, Attributi attributi, Equipaggiamento equipaggiamento, std::string posToFile): attributi(attributi) {
	
		this->nome = nome;
		this->equipaggiamento = equipaggiamento;
		this->inventario = inventario;
		this->attributi = attributi;
		this->pathToTile = posToFile;
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
	distanza = attributi.getDestrezza()/8+1;
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
	if (equipaggiamento.getArmaPrimaria() == nullptr) {
		return Danno(std::vector<double>{1}, -1);
	}
	auto danno = equipaggiamento.getArmaPrimaria()->attacca();
	if (danno.getAmmontare() > 0) //is this even impossible
	{
		if (equipaggiamento.getArmaPrimaria()->getPeso() < 0.5) //arma piccola usa la destrezza
			danno.magnifica((double)attributi.getDestrezza() / 4);
		else										//arma grande no
			danno.magnifica((double)attributi.getForza() / 4);
		srand((unsigned int)time(nullptr));
		double random;
		random = rand() % 6;
		random = random / 12;
		random = random - (double)(1 / 6);
		random = 1 - random;
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

//TODO spostami in protagonista, visto che dovrebbe essere l'unico con l'UI
bool Entita::equip(int posizioneOggetto)
{
	if(posizioneOggetto>0&&(unsigned int)posizioneOggetto<inventario.size())
		if (equipaggiamento.equipaggia(inventario.at(posizioneOggetto))) {
			inventario.erase(inventario.begin()+posizioneOggetto);
			return true;
		}
	return false;
}

//TODO spostami in protagonista, visto che dovrebbe essere l'unico con l'UI
bool Entita::equip(sf::RenderWindow& window, TextBox& messages) 
{
	UtilityGrafica finestra; //CHECK in caso di Refresh passare sprite
	int numero = 0;
	std::cout << std::endl;
	for each (auto oggetto in inventario)
	{
		std::cout << numero << ") " << oggetto->getNome() << " --> " << oggetto->getDescrizione() << std::endl;
		messages.text.setString(messages.text.getString() + std::to_string(numero) + ") " + oggetto->getNome() + " --> " + oggetto->getDescrizione() + "\n");
		numero++;
	}
	std::cout << "Inserisci il numero dell'oggetto da inserire (Invio per confermare): ";
	messages.text.setString(messages.text.getString() + "Inserisci il numero dell'oggetto da inserire (Invio per confermare): ");


	//FIXME funziono solo con numeri, non forzarmi please
	//std::cin >> numero; 
	
	auto convert = finestra.graphicInput2( messages.text.getString() );
	try {
		numero = std::stoi(convert.toAnsiString(), nullptr);
	}
	catch (std::exception const & e){
		std::cout << "Input invalido" << std::endl;
		messages.text.setString("Input invalido\n");
		return false;
	}
	if (numero >= 0 && (unsigned int)numero < inventario.size()) 
	{
		messages.text.setString("");
		
		return equip(numero);
	}
	else 
	{
		std::cout << "Non ho potuto equipaggiare l'oggetto perche' non so come si fa." << std::endl;
		messages.text.setString("Non ho potuto equipaggiare l'oggetto perche' non so come si fa.\n");
		return false;
	}
}



bool Entita::addInventario(std::shared_ptr<Oggetto> oggettoDaAgginugere)
{
	inventario.push_back(oggettoDaAgginugere);
	return true;
	//CHECK posso fallire, cosa potrebbe andare male?
}

//return true se uccide, false altrimenti
bool Entita::subisciDanno(Danno dannoSubito, TextBox& messages)
{
	double totalehp = 0;
	//LOOKATME potremmo per esempio lasciare che alcuni tipi di danno abbiano altri effetti, tipo il danno mentale infligge danni alla barra delle magia
	for (unsigned int i = 0; i < Danno::giveCategoriaDanni().size();i++)
	{
		totalehp += attributi.getResistenze()[i] * dannoSubito.getParteDanno(i);
	}
	if (totalehp <= 0) {
		std::cout << nome << " e' rimasto incolume!" << std::endl;
		messages.text.setString(messages.text.getString() + nome + " "+ sf::String(sf::Uint32(232)) +" rimasto incolume! \n");
		return false;
	}
	attributi.setHp((int)(attributi.getHp()-totalehp));
	if (attributi.getHp() < 0) { //dead
		onDeath(messages);
		return true;
	}
	std::cout << nome << " ha sofferto " << (int)totalehp << " danni!" << std::endl;
	messages.text.setString(messages.text.getString() + nome + " ha sofferto " + std::to_string((int)totalehp) + " danni!\n");
	return false;
}


double Entita::carryWeight()
{ //Calcola il carico trasportato
	double total = 0;
	for (auto i : inventario) 
	{
		total += i->getPeso();
	}
	total += equipaggiamento.getPeso();	// più vicini al centro di massa (l'entità che li solleva) serve meno sforzo per
	return total;						// sollevarli.
}


void Entita::onDeath(TextBox& messages)
{
	auto peso = attributi.getForza() * 10 + attributi.getTempra() * 10 + attributi.getDestrezza() * 2 + attributi.getIntelligenza()*0.25; //L'intelligenza significa la dimensione del cervello. L'intelligenza non dipende dalla quantità di cervello nel mondo reale (dipende dalle sinapsi), ma questo è un gioco.
	auto object = std::make_shared<Oggetto>(Oggetto(peso, "Cadavere di " + nome, "La carcassa di " + nome + " oramai esanime.", 0));
	addInventario(object);
	
	std::cout << nome << " e' morto!" << std::endl; //TODOFAR implementa sesso
	messages.text.setString(messages.text.getString() + nome + " e' morto!\n" );
}

std::string Entita::describeInventario() {
	std::string returnStringa;
	for (auto i = inventario.begin(); i != inventario.end(); i++) {
		returnStringa.append(i->get()->getNome());
		returnStringa.append(" --> ");
		returnStringa.append(i->get()->getDescrizione());
		returnStringa.append("\n");
	}
	return returnStringa;
}
