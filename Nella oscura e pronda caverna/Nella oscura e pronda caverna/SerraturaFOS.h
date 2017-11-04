#pragma once
#include "Serratura.h"
#include <iostream>
#include <cmath>
class SerraturaFOS :
	public Serratura
{
public:
	SerraturaFOS(double angolo, double tolleranzaAngolo, double distanza, double tolleranzaDistanza);
	~SerraturaFOS();
	int scassina();
	double prendiAngolo();
	double prendiDistanza();
private:
	double angolo;
	double tolleranzaAngolo;
	double distanza;
	double tolleranzaDistanza;
	sf::RenderWindow finestraSerratura;
	sf::Font fontTesto;
};

