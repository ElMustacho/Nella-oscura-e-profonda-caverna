#include "MonsterFactory.h"


std::unique_ptr<Entita> MonsterFactory::makeMonRandUnique(int code)
{
	std::unique_ptr<Entita> appoggio;
	int spawned;
	if (code = -1) {
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_real_distribution<double> dist(0, 3);
		spawned = dist(mt);
	}

	else
		spawned = code;
	switch (spawned)
	{
	case 0: {
		std::vector<std::shared_ptr<Oggetto>> inventario{ std::shared_ptr<Oggetto>(new Oggetto(0.5, "Targhetta identificativa", "Hai la prova di aver ucciso qualcuno.", 0)) };
		Attributi nellaMedia(4, 4, 2, 4, 4, 4, 4, 4);
		Equipaggiamento equipaggiamento;
		auto arma = std::make_shared<Arma>(2, "Ascia piccola", "Per piccoli eroi", 6, Danno({ 0,1 }, 8));
		equipaggiamento.equipaggia(arma);
		appoggio = std::make_unique<Attore>("Soldato semplice", inventario, nellaMedia, equipaggiamento, 500);
		return appoggio;
		break;
	}
	case 1: {
		std::vector<std::shared_ptr<Oggetto>> inventario{};
		Attributi nellaMedia(4, 2, 2, 4, 4, 4, 4, 4);
		Equipaggiamento equipaggiamento; //Picche, non hai nulla scemo
		auto torcia = std::make_shared<Arma>(0.25, "Torcia accesa", "Per scacciare il mostro di Frankenstain", 2, Danno({ 0,0,0.5,0,0.5 }, 6));
		equipaggiamento.equipaggia(torcia);
		appoggio = std::make_unique<Attore>("Popolano arrabbiato", inventario, nellaMedia, equipaggiamento, 500);
		return appoggio;
		break;
	}
	case 2: {
		std::vector<std::shared_ptr<Oggetto>> inventario{};
		Attributi nellaMedia(4, 2, 2, 4, 4, 8, 4, 4);
		Equipaggiamento equipaggiamento;
		auto segaArrugginita = std::make_shared<Arma>(0.25, "Sega arrugginita", "A rischio tetano", 2, Danno({ 0.5,0,0,0,0,0,0,0.5 }, 8));
		equipaggiamento.equipaggia(segaArrugginita);
		appoggio = std::make_unique<Attore>("Medico del medioevo", inventario, nellaMedia, equipaggiamento, 500);
		return appoggio;
		break;
	}
	default:
	{
		{
			std::vector<std::shared_ptr<Oggetto>> inventario;
			Attributi scarso(3, 4, 2, 2, 2, 1, 3, 1);
			Equipaggiamento equipaggiamento;
			auto spadinoDiLegno = std::make_shared<Arma>(0.25, "Spadino di legno", "Non affilato", 2, Danno({0,0,1}, 2));
			appoggio = std::make_unique<Attore>("Goblin puzzone", inventario, scarso, equipaggiamento, 1.1);
			break;
		}
	}
		break;
	}
	return appoggio;
}
std::shared_ptr<Entita> MonsterFactory::makeMonRand(int code)
{
	std::shared_ptr<Entita> ptrReturned(makeMonRandUnique(code));
	return ptrReturned;
}

MonsterFactory::MonsterFactory(std::vector<std::shared_ptr<Entita>> entitaPossibili)
{
	entita = entitaPossibili;
}

void MonsterFactory::setMonsterList(std::vector<std::shared_ptr<Entita>> entitaPossibili)
{
	entita = entitaPossibili;
}

std::shared_ptr<Entita> MonsterFactory::makeMon(int code) 
{
	std::shared_ptr<Entita> ptrReturned(makeMonUnique(code));
	return ptrReturned;
}

std::unique_ptr<Entita> MonsterFactory::makeMonUnique(int code)
{
	if (entita.empty()) {
		return makeMonRandUnique(code);
	}
	else {
		if (code == -1) {
			std::random_device rd;
			std::mt19937 mt(rd());
			std::uniform_real_distribution<double> dist(0, entita.size());
			auto entToCopy = std::dynamic_pointer_cast<Attore>(entita[(int)dist(rd)]);
			return std::make_unique<Attore>(*entToCopy);
		}
		else {
			auto entToCopy = std::dynamic_pointer_cast<Attore>(entita[code%entita.size()]);
			return std::make_unique<Attore>(*entToCopy);
		}
	}
}
	

MonsterFactory::MonsterFactory()
{
}


MonsterFactory::~MonsterFactory()
{
}
