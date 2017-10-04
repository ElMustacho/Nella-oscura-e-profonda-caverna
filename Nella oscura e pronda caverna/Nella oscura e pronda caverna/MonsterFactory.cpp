#include "MonsterFactory.h"



std::shared_ptr<Entita> MonsterFactory::makeMon(int code)
{
	std::shared_ptr<Entita> appoggio;
	if (code = -1) {
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_real_distribution<double> dist(0,3);
		int spawned = dist(mt);
		switch (spawned)
		{
		case 0: {
			std::vector<std::shared_ptr<Oggetto>> inventario{ std::shared_ptr<Oggetto>(new Oggetto(0.5, "Targhetta identificativa", "Hai la prova di aver ucciso qualcuno.", 0)) };
			Attributi nellaMedia(4, 4, 2, 4, 4, 4, 4, 4);
			Equipaggiamento equipaggiamento;
			appoggio = std::make_shared<Attore>("Soldato semplice", inventario, nellaMedia, equipaggiamento, 1);
			return appoggio;
			break;
		}
		case 1: {
			std::vector<std::shared_ptr<Oggetto>> inventario{};
			Attributi nellaMedia(4, 4, 2, 4, 4, 4, 4, 4);
			Equipaggiamento equipaggiamento; //Picche, non hai nulla scemo
			auto torcia = std::make_shared<Arma>(0.25, "Torcia accesa", "Per scacciare il mostro di Frankenstain", 2, Danno({ 0,0,0.5,0,0.5 }, 6));
			equipaggiamento.equipaggia(torcia);
			appoggio = std::make_shared<Attore>("Popolano arrabbiato", inventario, nellaMedia, equipaggiamento, 1);
			return appoggio;
			break;
		}
		case 2: {
			std::vector<std::shared_ptr<Oggetto>> inventario{};
			Attributi nellaMedia(4, 4, 2, 4, 4, 8, 4, 4);
			Equipaggiamento equipaggiamento;
			auto segaArrugginita = std::make_shared<Arma>(0.25, "Sega arrugginita", "A rischio tetano", 2, Danno({ 0.5,0,0,0,0,0,0,0.5 }, 8));
			equipaggiamento.equipaggia(segaArrugginita);
			appoggio = std::make_shared<Attore>("Medico del medioevo", inventario, nellaMedia, equipaggiamento, 1);
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
				appoggio = std::make_shared<Attore>("Goblin puzzone", inventario, scarso, equipaggiamento, 1.1);
				break;
			}
		}
			break;
		}
	}
	
	return appoggio;
}

MonsterFactory::MonsterFactory()
{
}


MonsterFactory::~MonsterFactory()
{
}
