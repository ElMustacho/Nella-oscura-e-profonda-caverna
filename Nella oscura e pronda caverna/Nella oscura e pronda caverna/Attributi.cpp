#include "Attributi.h"

Attributi::Attributi(int forza, int destrezza, int tempra, int intelligenza, int spirito, int carisma, int fortuna, int hp, int potereMagico, int stamina, double forzaDiCarico, int maxHp, int maxPotereMagico, int maxStamina, bool silenzioso)
{
	this->forza = forza;
	this->destrezza = destrezza;
	this->tempra = tempra;
	this->intelligenza = intelligenza;
	this->spirito = spirito;
	this->carisma = carisma;
	this->fortuna = fortuna;
	this->hp = hp;
	this->potereMagico = potereMagico;
	this->stamina = stamina;
	this->forzaDiCarico = forzaDiCarico;
	this->maxHp = hp;
	this->maxPotereMagico = potereMagico;
	this->maxStamina = stamina;
	this->silenzioso = silenzioso;
}

Attributi::Attributi(int forza, int destrezza, int tempra, int intelligenza, int spirito, int carisma, int fortuna, int livello) {
	this->forza = forza;
	this->destrezza = destrezza;
	this->tempra = tempra;
	this->intelligenza = intelligenza;
	this->spirito = spirito;
	this->carisma = carisma;
	this->fortuna = fortuna;
	maxHp =(int) ((5 + (tempra) * 2 + (int)(forza)*0.5)*livello);
	maxPotereMagico =(int) ((5 + (intelligenza) * 2 + (int)(spirito)*0.5)*livello);
	maxStamina = (5 + tempra + destrezza + spirito)*livello;
	hp = maxHp;
	potereMagico = maxPotereMagico;
	stamina = maxStamina;
	forzaDiCarico = (forza * 10 + 1)*(forza / 8);
	if (destrezza >7&&livello > 10) { //Segnala se l'entità è percepibile aldilà della vista

	}
}



Attributi::~Attributi()
{
}
