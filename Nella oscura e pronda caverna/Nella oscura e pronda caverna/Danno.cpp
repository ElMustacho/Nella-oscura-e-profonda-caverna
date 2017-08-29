#include "Danno.h"
#include <algorithm> //serve per std::find
/*Non c'è bisogno di passare un vettore completo; se uso solo contundente e magico posso omettere la creazione di 0 nel vector dopo magico (posizione 3)
Vettori più grandi vengono riportati ad una dimensione pari a quella della quantità di tipi.*/
Danno::Danno(std::vector<double> partiDanno, double ammontare)
{
	tipo.insert(tipo.begin(), partiDanno.begin(), partiDanno.end());
	tipo.resize(giveCategoriaDanni().size());
	this->ammontare = ammontare;
	equalize(false);
}


//Se true rinormalizza il danno (si veda nei test), altrimenti riproporziona il vector tipo
void Danno::equalize(bool alteraAmmontare) 
{
	double totale = 0;
	int qualcunoZero = 0;
	for each(double numero in tipo) {
		totale += numero;
		if (numero != 0)
			qualcunoZero++;
	}
	if (qualcunoZero == 0) //Se sono tutti 0 non c'è un vero danno
		ammontare = 0;
	else {
		//Porta totale ad 1
		for each(double numero in tipo) {
			numero*=totale;
		}
		if (alteraAmmontare)
		{
			ammontare*=totale;
		}
	}
}

Danno::Danno()
{
}

Danno::~Danno()
{
}

//quando e se aggiungeremo altre categorie di danni questa sarà la cosa da modificare.
const std::vector<std::string> Danno::giveCategoriaDanni()
{
	return std::vector<std::string>  { "tagliente", "perforante", "contundente", "magico", "fuoco", "freddo", "elettrico", "acido",
		"sonico", "sacro", "sacrilego", "esplosivo", "positivo", "negativo", "mentale", "forza" };
}
// percentuale = 0.5 -> categoria dimezzata, percentuale = 1.5 -> categoria aumentata della metà
void Danno::magnifica(int posizione, double percentuale)
{
	if (posizione<0 && (unsigned int) posizione > giveCategoriaDanni().size()) { //LOOKATME queste operazioni sono silenziose, andranno bene così?
		tipo.at(posizione) *= percentuale;						  //Comunque sono testabili.
		equalize(true);											  //Il controllo è se posizione è outofbound
	}
}
//CHECK Stessa funzione di prima, ma invocata tramite stringa (per chiarezza). Case sensitive (vogliamo che non lo sia?)
void Danno::magnifica(std::string posizione, double percentuale)
{
	auto tipiDanno = giveCategoriaDanni();
	auto it = std::find(tipiDanno.begin(), tipiDanno.end(), posizione); //ricerca stringa
	if (it!=tipiDanno.end()) //la stringa c'è
	{
		auto posizioneTipo = std::distance(tipiDanno.begin(), it); //trasforma stringa in numero, es. -> mentale = 14 / magico = 3
		tipo.at(posizioneTipo) *= percentuale;
		equalize(true);
	}
}
//Questa funzione semplicemente altera il totale del danno. Un danno con ammontare = 100, chiamando questa funzione con 1.2, arriva a 120
void Danno::magnifica(double percentuale)
{
	ammontare *= percentuale;
}

std::vector<double> const Danno::getTipo()
{
	return tipo;
}

void Danno::setTipo(std::vector<double> vectorTipo)
{
	tipo = vectorTipo;
}

double const Danno::getAmmontare()
{
	return ammontare;
}
//Restituisce l'ammontare del danno che solo un tipo di danno per volta produce
double const Danno::getParteDanno(int posizione)
{
	if (posizione>-1 &&(unsigned int) posizione<giveCategoriaDanni().size())
		return tipo.at(posizione)*ammontare;
	return 0; //Una parte di qualcosa che non esiste è 0
}
//Override tramite stringa
double const Danno::getParteDanno(std::string posizione)
{
	auto tipiDanno = giveCategoriaDanni();
	auto it = std::find(tipiDanno.begin(), tipiDanno.end(), posizione); //ricerca stringa
	if (it != tipiDanno.end()) //la stringa c'è
	{
		return tipo.at(std::distance(tipiDanno.begin(), it))*ammontare; //Garanzia che sia dentro il range del vector
	}
	return 0; //Una parte di qualcosa che non esiste è 0
}

void Danno::setParteDanno(std::string posizione, double ammontare)
{
	auto tipiDanno = giveCategoriaDanni();
	auto it = std::find(tipiDanno.begin(), tipiDanno.end(), posizione); //ricerca stringa
	if (it != tipiDanno.end()) //la stringa c'è
	{
		if(ammontare<0)
			tipo.at(std::distance(tipiDanno.begin(), it)) = 0;
		else
			tipo.at(std::distance(tipiDanno.begin(), it)) = ammontare;
		equalize(false);
	}
	
}

void Danno::setParteDanno(int posizione, double ammontare) {
	if (posizione > -1 && (unsigned int)posizione < giveCategoriaDanni().size()) {
		if (ammontare<0)
			tipo.at(posizione) = 0;
		else
			tipo.at(posizione) = ammontare;
		equalize(false);
	}
}
//Neutralità ad un tipo di danno -> 1// Doppi danni da un tipo -> 2// Immunità ad un tipo di danno -> 0 ectv
double const Danno::calcolaDannoTotale(std::vector<double> resistenze)
{
	double totale = 0;
	for (unsigned int i = 0; i < giveCategoriaDanni().size(); i++) {
		totale += getParteDanno(i)*(resistenze[i]);
	}
	return totale;
}
