#pragma once
#include "Entita.h"
class Attore : public Entita
{

public:
	Attore(std::string nome, std::vector<std::shared_ptr<Oggetto>> inventario, Attributi attributi, Equipaggiamento equipaggiamento, double experienceDrop, std::string posToFile="");
	double getExperienceDrop()const { return experienceDrop; };
	void setExperienceDrop(double experienceDrop) { this->experienceDrop = experienceDrop; };
	~Attore();
	void setStringToFile(std::string newPos) { posToFile = newPos; };
	std::string getStringToFile() const { return posToFile; };
private:
	double experienceDrop;
	std::string posToFile;
};

