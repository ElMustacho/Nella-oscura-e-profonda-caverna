#pragma once
#include "Serratura.h"
#include <iostream>
#include <cmath>
class SerraturaFOS :
	public Serratura
{
public:
	SerraturaFOS(double angolo, double tolleranza);
	~SerraturaFOS();
	int scassina();
	double prendiAngolo();
private:
	double angolo;
	double tolleranza;
	sf::RenderWindow finestraSerratura;
	sf::Font fontTesto;
};

