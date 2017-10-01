#pragma once

#include "Attributi.h"
#include "Oggetto.h"
#include "Equipaggiamento.h"


class Observer
{

public:
	virtual void update(unsigned int lv, double exp, long int money, std::string name, Attributi attr, std::vector<std::shared_ptr<Oggetto>> inventory, Equipaggiamento equip) = 0;

protected:
	//Observer() {};
	virtual ~Observer();
private:
	//Observer(const Observer& ref);
	//Observer& operator=(const Observer& ref);
};

