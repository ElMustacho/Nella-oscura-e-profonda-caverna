#pragma once

#include "Attributi.h"
#include "Oggetto.h"
#include "Equipaggiamento.h"


class Observer
{

public:
	virtual void update(unsigned int lv, double exp, long int money) = 0;

protected:
	//Observer() {};
	virtual ~Observer() {};

};

