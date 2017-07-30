#include <vector>
#pragma once
class Danno
{
	//La forma standard di un danno è che la sommatoria del vector "tipo" sia 1, se è 0<x<1 oppure 1>x>tanto 
	//viene proporzionato ad 1, altrimenti ammontare va a 0. Valori negativi di "ammontare" significa curare
public:
	static enum cadtegoriaDanni {
		tagliente = 0, perforante = 1, contundente = 2, magico = 3, fuoco = 4, freddo = 5, elettrico = 6, acido = 7,
		sonico = 8, sacro = 9, sacrilego = 10, esplosivo = 11, positivo = 12, negativo = 13, mentale = 14, forza = 15
	};
	//Riporta il danno in forma standard
	void equalize(); 
	Danno(std::vector<double> partiDanno, double ammontare);
	//shortcut per fare un danno nullo
	Danno(bool noDanno);
	~Danno();
	static const std::vector<std::string> categoriaDanni;
private:
	
	std::vector<double> tipo;
	double ammontare;
};
//quando e se aggiungeremo altre categorie questa sarà la cosa da modificare.
const std::vector<std::string> categoriaDanni = { "tagliente", "perforante", "contundente", "magico", "fuoco", "freddo", "elettrico", "acido",
"sonico", "sacro", "sacrilego", "esplosivo", "positivo", "negativo", "mentale", "forza"};