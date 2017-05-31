#pragma once

class Attributi
{

public:
	Attributi(); // CHECK without this the whole program didn't want to start
	Attributi(int forza, int destrezza, int tempra, int intelligenza, int spirito, int carisma, int fortuna, int hp, int potereMagico, int stamina, double forzaDiCarico, int maxHp, int maxPotereMagico, int maxStamina); //usato quando si carica un salvataggio o dal protagonista all'inizio del gioco.
	Attributi(int forza, int destrezza, int tempra, int intelligenza, int spirito, int carisma, int fortuna, int livello); //autogenera le caratteristiche rimanenti
	~Attributi();

	int getCarisma() const 
	{
		return carisma;
	}

	void setCarisma(int carisma) 
	{
		this->carisma = carisma;
	}

	int getDestezza() const
	{
		return destezza;
	}

	void setDestezza(int destezza)
	{
		this->destezza = destezza;
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

	void setHp(int hp) 
	{
		this->hp = hp;
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

private:
	int forza;
	int destezza;
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
};

