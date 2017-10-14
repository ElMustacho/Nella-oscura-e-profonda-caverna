#pragma once
#include "Entita.h"
#include "Subject.h"
#include "Observer.h"
class Protagonista : public Entita, public Subject
{

public:
	Protagonista(std::string nome, std::vector<std::shared_ptr<Oggetto>> inventario, Attributi attributi, Equipaggiamento equipaggiamento, unsigned int livello, double esperienza, long int fondiEconomici, std::string posToFile="");
	void update();
	~Protagonista();
	virtual bool subisciDanno(Danno dannoSubito, TextBox& messages);
	double getEsperienza() const { return esperienza; } ;
	void setEsperienza(double esperienza) { this->esperienza = esperienza; };
	unsigned int getLivello() const { return livello; };
	virtual void onDeath(TextBox& messages) override;
	void attachGraphic(Observer* obs);
	void regeneration();
	void guadagnaEsperienza(double experienceGain);
	void updateLevel();
private:
	unsigned int livello; //FIXME livello è gia contenuto dentro attributi, ereditati da Entita
	double esperienza;
	long int fondiEconomici;
	void* graphic;
	double regenerationMemory;
};

