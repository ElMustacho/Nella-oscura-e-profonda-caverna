#pragma once
#include <memory>
#include <random>
#include "Oggetto.h"
#include "Arma.h"
class ObjectFactory
{
public:
	static std::shared_ptr<Oggetto> makeObjRand(int code = -1);
	static std::shared_ptr<Oggetto> makeWeapRand(int code = -1);
	std::shared_ptr<Oggetto> makeObj(int code = -1);
	std::shared_ptr<Oggetto> makeWeap(int code = -1);
	void setObjList(std::vector<std::shared_ptr<Oggetto>> newOggettiGenerabili) { this->oggettiGenerabili = newOggettiGenerabili; };
	void setWeapList(std::vector<std::shared_ptr<Arma>> newOggettiGenerabili) { this->armiGenerabili = newOggettiGenerabili; };
	ObjectFactory();
	ObjectFactory(std::vector<std::shared_ptr<Oggetto>> oggettiGenerabili);
	ObjectFactory(std::vector<std::shared_ptr<Arma>> armiGenerabili);
	ObjectFactory(std::vector<std::shared_ptr<Oggetto>> oggettiGenerabili, std::vector<std::shared_ptr<Arma>> armiGenerabili);
	~ObjectFactory();
private:

	std::vector<std::shared_ptr<Oggetto>> oggettiGenerabili;
	std::vector<std::shared_ptr<Arma>> armiGenerabili;
};

