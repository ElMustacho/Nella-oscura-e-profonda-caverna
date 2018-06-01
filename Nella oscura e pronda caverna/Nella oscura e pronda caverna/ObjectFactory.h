#pragma once
#include <memory>
#include <random>
#include "Oggetto.h"
#include "Arma.h"
class ObjectFactory
{
public:
	static std::shared_ptr<Oggetto> makeObjRand(int code = -1);
	static std::unique_ptr<Oggetto> makeObjRandUnique(int code);
	static std::shared_ptr<Oggetto> makeWeapRand(int code = -1);
	static std::unique_ptr<Oggetto> makeWeapRandUnique(int code = -1);

	std::shared_ptr<Oggetto> makeObj(int code = -1);
	std::unique_ptr<Oggetto> makeObjUnique(int code = -1);
	std::shared_ptr<Oggetto> makeWeap(int code = -1);
	std::unique_ptr<Oggetto> makeWeapUnique(int code = -1);

	void setObjList(std::vector<std::shared_ptr<Oggetto>> newOggettiGenerabili);
	void setWeapList(std::vector<std::shared_ptr<Arma>> newOggettiGenerabili);

	ObjectFactory();
	ObjectFactory(std::vector<std::shared_ptr<Oggetto>> oggettiGenerabili);
	ObjectFactory(std::vector<std::shared_ptr<Arma>> armiGenerabili);
	ObjectFactory(std::vector<std::shared_ptr<Oggetto>> oggettiGenerabili, std::vector<std::shared_ptr<Arma>> armiGenerabili);
	~ObjectFactory();
private:

	std::vector<std::shared_ptr<Oggetto>> oggettiGenerabili;
	std::vector<std::shared_ptr<Arma>> armiGenerabili;
};

