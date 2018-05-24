#include "Attributi.h"
#include <vector>
#include <random>
Attributi::Attributi(int forza, int destrezza, int tempra, int intelligenza, int spirito, int carisma, int fortuna, int hp, int potereMagico, int stamina, double forzaDiCarico, int maxHp, int maxPotereMagico, int maxStamina, bool silenzioso, std::vector<double> resistenze)

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
	this->resistenze = resistenze;
}

Attributi::Attributi()
{
}
Attributi::Attributi(bool randomGeneration) {

	if (randomGeneration == false)
	{

		this->forza = 0;
		this->destrezza = 0;
		this->tempra = 0;
		this->intelligenza = 0;
		this->spirito = 0;
		this->carisma = 0;
		this->fortuna = 0;
		this->hp = 1;
		this->potereMagico = 0;
		this->stamina = 0;
		this->forzaDiCarico = 0;
		this->maxHp = 1;
		this->maxPotereMagico = 0;
		this->maxStamina = 0;
		this->silenzioso = 0;
		this->resistenze = {};
	}
	else {

		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_real_distribution<double> dist(0, 10);

		this->forza = dist(mt);
		this->destrezza = dist(mt);
		this->tempra = dist(mt);
		this->intelligenza = dist(mt);
		this->spirito = dist(mt);
		this->carisma = dist(mt);
		this->fortuna = dist(mt);
		this->hp = dist(mt)+15;
		this->potereMagico = dist(mt);
		this->stamina = dist(mt);
		this->forzaDiCarico = dist(mt);
		this->maxHp = this->hp;
		this->maxPotereMagico = this->maxPotereMagico;
		this->maxStamina = this->maxStamina;
		this->silenzioso = 0;
		this->resistenze = {};
	}
}

Attributi::Attributi(int forza, int destrezza, int tempra, int intelligenza, int spirito, int carisma, int fortuna, int livello, std::vector<double> resistenze) {
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
	forzaDiCarico = (forza * 10 + 1)*(double)(forza / 8.);
	if (destrezza > 7 && livello > 10) { //Segnala se l'entità è percepibile aldilà della vista
		silenzioso = true;
	}
	this->resistenze = resistenze;
	
}

bool Attributi::operator==(const Attributi & rAttr) const
{
	if (this->forza == rAttr.forza)
		if (this->destrezza == rAttr.destrezza)
			if (this->tempra == rAttr.tempra)
				if (this->intelligenza == rAttr.intelligenza)
					if (this->spirito == rAttr.spirito)
						if (this->carisma == rAttr.carisma)
							if (this->fortuna == rAttr.fortuna)
								if (this->hp == rAttr.hp)
									if (this->potereMagico == rAttr.potereMagico)
										if (this->stamina == rAttr.stamina)
											if (this->forzaDiCarico == rAttr.forzaDiCarico)
												if (this->maxHp == rAttr.maxHp)
													if (this->maxPotereMagico == rAttr.maxPotereMagico)
														if (this->maxStamina == rAttr.maxStamina)
															if (this->silenzioso == rAttr.silenzioso)
																if (this->resistenze == rAttr.resistenze)
																	return true;
	return false;
}

Attributi::~Attributi()
{
}
