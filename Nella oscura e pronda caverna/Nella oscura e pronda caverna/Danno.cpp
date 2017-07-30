#include "Danno.h"
#include <algorithm> //serve per std::find
Danno::Danno(std::vector<double> partiDanno, double ammontare)
{
	tipo.insert(tipo.begin(), partiDanno.begin(), partiDanno.end());
	this->ammontare = ammontare;
	equalize(false);
}

Danno::Danno() {
	tipo.reserve(giveCategoriaDanni().size());
	for each (double numero in tipo) {
		numero = 0;
	}
	ammontare = 0;
}
//Se true rinormalizza il danno (si veda nei test), altrimenti riproporziona il vector tipo
void Danno::equalize(bool alteraAmmontare) 
{
	double totale = 0;
	int qualcunoZero = 0;
	for each(double numero in tipo) {
		totale += numero;
		if (numero == 0)
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

Danno::~Danno()
{
}

//quando e se aggiungeremo altre categorie di danni questa sarà la cosa da modificare.
std::vector<std::string> Danno::giveCategoriaDanni()
{
	//LOOKATME lo possiamo fare in una sola riga?
	std::vector<std::string> tmp = { "tagliente", "perforante", "contundente", "magico", "fuoco", "freddo", "elettrico", "acido",
		"sonico", "sacro", "sacrilego", "esplosivo", "positivo", "negativo", "mentale", "forza" };
	return tmp;
}
// percentuale = 0.5 -> categoria dimezzata, percentuale = 1.5 -> categoria aumentata della metà
void Danno::magnifica(int posizione, double percentuale)
{
	if (posizione<0 || posizione > giveCategoriaDanni().size()) { //LOOKATME queste operazioni sono silenziose, andranno bene così?
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
