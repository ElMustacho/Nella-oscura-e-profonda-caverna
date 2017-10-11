#pragma once

#include "Attributi.h"
#include "Oggetto.h"
#include "Equipaggiamento.h"


class Observer
{

public:
	virtual void update() = 0;
	virtual void disconnect() = 0;

protected:
	//Observer() {};
	virtual ~Observer() {};

};

