#include "ObjectFactory.h"

std::shared_ptr<Oggetto> ObjectFactory::makeObjRand(int code) {
	std::shared_ptr<Oggetto> ptrReturned(makeObjRandUnique(code));
	return ptrReturned;
}

std::unique_ptr<Oggetto> ObjectFactory::makeObjRandUnique(int code)
{
	std::unique_ptr<Oggetto> appoggio;
	int spawned;
	if (code = -1) {
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_real_distribution<double> dist(0, 3);
		spawned = (int)dist(mt);
	}
	else
		spawned = code;
	switch (spawned){
	case 0: {
		appoggio = std::make_unique<Oggetto>(0.1, "Pacchetto di fazzoletti", "Per asciugarsi il naso", 1);
		break; 
	}
	case 1: {
		appoggio = std::make_unique<Oggetto>(0.2, "Piatto di coccio", "Utensile per mangiare", 1);
		break;
	}
	case 2: {
		appoggio = std::make_unique<Oggetto>(1, "Razione di cibo", "Dal sapore blando", 1);
		break;
	}
	default: {
		appoggio = std::make_unique<Oggetto>(0.5, "Cubo di Rubik", "Un rompicapo senza tempo", 14);
	}
	}
	return appoggio;
}

std::shared_ptr<Oggetto> ObjectFactory::makeWeapRand(int code) {
	std::shared_ptr<Oggetto> ptrReturned(makeWeapRandUnique(code));
	return ptrReturned;
}

std::unique_ptr<Oggetto> ObjectFactory::makeWeapRandUnique(int code)
{
	std::unique_ptr<Oggetto> appoggio;
	int spawned;
	if (code = -1) {
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_real_distribution<double> dist(0, 3);
		spawned = (int)dist(mt);
	}
	else
		spawned = code;
	switch (spawned) {
	case 0: {
		appoggio = std::make_unique<Arma>(3, "Spada semplice", "Un'arma ordinaria", 15, Danno({1},20));
		break;
	}
	case 1: {
		appoggio = std::make_unique<Arma>(3, "Mazza semplice", "Un'arma ordinaria", 15, Danno({0,0,1},20));
		break;
	}
	case 2: {
		appoggio = std::make_unique<Arma>(3, "Ascia semplice", "Un'arma ordinaria", 15, Danno({ 0,1 }, 20));
		break;
	}
	default: {
		appoggio = std::make_unique<Arma>(0.5, "Pugnale semplice", "Una piccola arma ordinaria", 14, Danno({ 0,1 },20));
	}
	}
	return appoggio;
}
//Se la lista degli oggetti generabili � vuota ne restituisce uno della classe statica
std::shared_ptr<Oggetto> ObjectFactory::makeObj(int code) {
	std::shared_ptr<Oggetto> ptrReturned(makeObjUnique(code));
	return ptrReturned;
}


std::unique_ptr<Oggetto> ObjectFactory::makeObjUnique(int code)
{
	if (oggettiGenerabili.empty())
		return makeObjRandUnique(code);
	else {
		if(code==-1){
			std::random_device rd;
			std::mt19937 mt(rd());
			std::uniform_real_distribution<double> dist(0, oggettiGenerabili.size());
			std::shared_ptr<Oggetto> objToCopy = oggettiGenerabili[(int)dist(rd)];
			auto ifThisIsAWeapon = std::dynamic_pointer_cast<Arma>(objToCopy);
			//TODOFAR creare un deep copier indipendente dal tipo di oggetto
			if (ifThisIsAWeapon != nullptr)
			{
				return std::make_unique<Arma>(*ifThisIsAWeapon);
			}
			return std::make_unique<Oggetto>(*objToCopy);
		}
		else {
			std::shared_ptr<Oggetto> objToCopy = oggettiGenerabili[code%oggettiGenerabili.size()];
			auto ifThisIsAWeapon = std::dynamic_pointer_cast<Arma>(objToCopy);
			//TODOFAR creare un deep copier indipendente dal tipo di oggetto
			if (ifThisIsAWeapon != nullptr)
			{
				return std::make_unique<Arma>(*ifThisIsAWeapon);
			}
			return std::make_unique<Oggetto>(*objToCopy);
		}
	}
}
std::shared_ptr<Oggetto> ObjectFactory::makeWeap(int code)
{
	std::shared_ptr<Oggetto> ptrReturned(makeWeapUnique(code));
	return ptrReturned;
}
//Se la lista delle armi generabili � vuota ne restituisce una della classe statica
std::unique_ptr<Oggetto> ObjectFactory::makeWeapUnique(int code)
{
	if (armiGenerabili.empty())
		return makeWeapRandUnique(code);
	else {
		if (code == -1) {
			std::random_device rd;
			std::mt19937 mt(rd());
			std::uniform_real_distribution<double> dist(0, armiGenerabili.size());
			std::shared_ptr<Arma> weapToCopy = armiGenerabili[(int)dist(rd)];
			return std::make_unique<Arma>(*weapToCopy);
		}
		else {
			std::shared_ptr<Arma> weapToCopy = armiGenerabili[code%armiGenerabili.size()];
			return std::make_unique<Arma>(*weapToCopy);
		}
	}
}

void ObjectFactory::setObjList(std::vector<std::shared_ptr<Oggetto>> newOggettiGenerabili)
{

	this->oggettiGenerabili = newOggettiGenerabili;
}

void ObjectFactory::setWeapList(std::vector<std::shared_ptr<Arma>> newOggettiGenerabili)
{
	this->armiGenerabili = newOggettiGenerabili;
}

ObjectFactory::ObjectFactory()
{
}

ObjectFactory::ObjectFactory(std::vector<std::shared_ptr<Arma>> armiGenerabili)
{
	this->armiGenerabili = armiGenerabili;
}

ObjectFactory::ObjectFactory(std::vector<std::shared_ptr<Oggetto>> oggettiGenerabili)
{

	this->oggettiGenerabili = oggettiGenerabili;
}

ObjectFactory::ObjectFactory(std::vector<std::shared_ptr<Oggetto>> oggettiGenerabili, std::vector<std::shared_ptr<Arma>> armiGenerabili)
{
	this->armiGenerabili = armiGenerabili;
	this->oggettiGenerabili = oggettiGenerabili;
}


ObjectFactory::~ObjectFactory()
{
}
