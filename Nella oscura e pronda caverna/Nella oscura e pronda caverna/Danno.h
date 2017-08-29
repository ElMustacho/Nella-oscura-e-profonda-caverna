#include <vector>
#pragma once
/*
Come si può notare non c'è nulla dettato da qualcosa di random, ed il motivo è che, per fare un esempio, che una freccia
scoccata da un'arco si comporta sempre come ogni altra freccia (stessa forma, stessa velocità etc. etc.), ma l'effetto
che tale freccia ha dipende esclusivamente da chi se la busca e da chi la lancia. Un carro armato la ignora, un essere umano 
decisamente meno. D'altra parte, un bambino sopravvive ad una freccia scoccata da un tetraplegico e un elefante esplode se
la freccia è scoccata da un obice ferroviario.
*/

class Danno
{
	//La forma standard di un danno è che la sommatoria del vector "tipo" sia 1, se è x!=0 
	//viene proporzionato ad 1, altrimenti ammontare va a 0. Valori negativi di "ammontare" significa curare
public:
	//Riporta il danno in forma standard
	void equalize(bool alteraAmmontare);
	Danno(std::vector<double> partiDanno, double ammontare);
	//non usarmi mai, servo per far instanziare altri oggetti
	Danno(); 
	~Danno();
	static const std::vector<std::string> giveCategoriaDanni();
	void magnifica(int posizione, double percentuale);
	void magnifica(std::string posizione, double percentuale);
	void magnifica(double percentuale);
	std::vector<double> const getTipo();
	void setTipo(std::vector<double> vectorTipo);
	double const getAmmontare();
	double const getParteDanno(int posizione);
	double const getParteDanno(std::string posizione);
	void setParteDanno(std::string posizione, double ammontare);
	void setParteDanno(int posizione, double ammontare);

	double const calcolaDannoTotale(std::vector<double> resistenze);
private:
	std::vector<double> tipo;
	double ammontare;
	//TODOFAR inserire probabilità critico e probabilità fallimento
};
