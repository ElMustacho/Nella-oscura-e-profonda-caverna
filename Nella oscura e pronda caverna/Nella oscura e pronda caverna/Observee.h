#pragma once
#include <vector>
#include <algorithm>

#include "Observer.h"


class Observee
{

public:
	//TODO revise this
	virtual bool registerObserver(Observer* obs) = 0;
	virtual bool removeObserver(Observer* obs) = 0;
	virtual bool notifyObservers() const = 0;

protected:
	//Observee();
	virtual ~Observee() {};

};

