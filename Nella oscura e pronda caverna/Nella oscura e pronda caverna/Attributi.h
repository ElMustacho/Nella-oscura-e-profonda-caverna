#pragma once
#include <vector>
class Attributi
{

public:

	Attributi(int forza, int destrezza, int tempra, int intelligenza, int spirito, int carisma, int fortuna, int hp, int potereMagico, int stamina, double forzaDiCarico, int maxHp, int maxPotereMagico, int maxStamina, bool silenzioso, std::vector<double> resistenze); //usato quando si carica un salvataggio o dal protagonista all'inizio del gioco.
	Attributi();
	Attributi(int forza, int destrezza, int tempra, int intelligenza, int spirito, int carisma, int fortuna, int livello, std::vector<double> resistenze = { 1,1,1,1,1,1,1,1,1,-1,1,1,1,1,1,1 }); //autogenera le caratteristiche rimanenti
	bool operator==(const Attributi & rAttr) const;
	~Attributi();

	int getCarisma() const
	{
		return carisma;
	}

	void setCarisma(int carisma)
	{
		this->carisma = carisma;
	}


	int getDestrezza() const {
		return destrezza;
	}

	void setDestrezza(int destrezza) {
		this->destrezza = destrezza;
	}

	int getFortuna() const
	{
		return fortuna;
	}

	void setFortuna(int fortuna)
	{
		this->fortuna = fortuna;
	}

	int getForza() const
	{
		return forza;
	}

	void setForza(int forza)
	{
		this->forza = forza;
	}

	double getForzaDiCarico() const
	{
		return forzaDiCarico;
	}

	void setForzaDiCarico(double forzaDiCarico)
	{
		this->forzaDiCarico = forzaDiCarico;
	}

	int getHp() const
	{
		return hp;
	}

	void setHp(int hp) {
		if (hp > maxHp)
			this->hp = maxHp;
		else {
			this->hp = hp;
		}
	}

	int getIntelligenza() const
		{
		return intelligenza;
		}

	void setIntelligenza(int intelligenza)
	{
		this->intelligenza = intelligenza;
	}

	int getPotereMagico() const
	{
		return potereMagico;
	}

	void setPotereMagico(int potereMagico) 
		{
			if (potereMagico > maxPotereMagico)
				this->potereMagico = maxPotereMagico;
			else
				this->potereMagico = potereMagico;
		}

		int getSpirito() const
		{
			return spirito;
		}

		void setSpirito(int spirito)
		{
			this->spirito = spirito;
		}

		int getStamina() const
		{
			return stamina;
		}


		void setStamina(int stamina) 
		{
			if (stamina > maxStamina)
				this->stamina = maxStamina;
			else
				this->stamina = stamina;
		}

		int getTempra() const
		{
			return tempra;
		}

		void setTempra(int tempra)
		{
			this->tempra = tempra;
		}

		int getMaxHp() const
		{
			return maxHp;
		}

		int getMaxPotereMagico() const
		{
			return maxPotereMagico;
		}

		int getMaxStamina() const
		{
			return maxStamina;
		}

		void setMaxStamina(int maxStamina) 
		{
			this->maxStamina = maxStamina;
		}

		void setMaxHp(int maxHp)
		{

			this->maxHp = maxHp;
		}

		void setMaxPotereMagico(int maxPotereMagico) 
		{
			this->maxPotereMagico = maxPotereMagico;
		}

		void setSilenziosio(bool silenzioso) 
		{
			this->silenzioso = silenzioso;
		}

		std::vector<double> getResistenze() const {
			return resistenze;
		}

		void setResistenze(std::vector<double> resistenze) {
			this->resistenze;
		}

		bool isSilenzioso() const
		{
			return silenzioso;
		}


private:
	std::vector<double> resistenze;
	int forza;
	int destrezza;
	int tempra;
	int intelligenza;
	int spirito;
	int carisma;
	int fortuna;
	int hp;
	int potereMagico;
	int stamina;
	int maxHp;
	int maxPotereMagico;
	int maxStamina;
	double forzaDiCarico;
	bool silenzioso;
	/* Questa roba la aggiungeremo quando non altre cose non avranno priorità.
	int sesso; //0 = maschio, 1 = femmina, 2 = neutro (nel senso che non ha sesso, tipo un golem, non che devono essere usati altri articoli)
	double peso; //per ora lo lascio come ottenibile dalle altre
	bool scava; //ignora pareti
	bool levita; //non tocca per terra
	bool teleporta; //teletrasporto
	bool incorporeo;
	bool nuota;

	blah blah blah
	*/
};
