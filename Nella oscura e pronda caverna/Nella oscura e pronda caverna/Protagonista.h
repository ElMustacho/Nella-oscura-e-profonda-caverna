#pragma once
#include "Entita.h"

class Protagonista : public Entita
{

public:
	Protagonista(std::string nome, std::list<std::shared_ptr<Oggetto>> inventario, Attributi attributi, std::vector<std::shared_ptr<Oggetto>> equipaggiamento, unsigned int livello, double esperienza, long int fondiEconomici);
	~Protagonista();
	double getEsperienza() const { return esperienza; } ;
	void setEsperienza(double esperienza) { this->esperienza = esperienza; };
	virtual void onDeath() override;
private:
	unsigned int livello; //FIXME livello è gia contenuto dentro attributi, ereditati da Entita
	double esperienza;
	long int fondiEconomici;
};

