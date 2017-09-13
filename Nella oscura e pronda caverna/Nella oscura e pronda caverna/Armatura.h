#pragma once
#include "Oggetto.h"

class Armatura :
	public Oggetto
{
public:
	Armatura(double peso, std::string nome, std::string descrizione, long valore, Danno resistenzaConferita);
	~Armatura();
	Danno getResistenza() const { return resistenzaConferita; };
	void setResistenza(Danno resistenzaConferita) { this->resistenzaConferita = resistenzaConferita; };
private:
	//0=nulla aggiunto, 1=protezione totale, -1=vulnerabilità 100%. 
	//Ammontare è usato come threshold, nel senso che i primi "Ammontare" danni vengono negati: se i danni totali scendono a meno 0 andranno a 0. 
	//Se è 0 le resistenze vanno a 0 quindi se si vuole dare un valore infimo di threshold basta usare un numero arbitrariamente vicino a 0 positivo
	//Valori negativi significa che arrivano più danni
	Danno resistenzaConferita;
	double threshold;
};

