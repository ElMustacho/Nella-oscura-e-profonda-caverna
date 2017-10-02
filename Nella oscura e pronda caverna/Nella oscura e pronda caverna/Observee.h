#pragma once
#include <vector>
#include <algorithm>

#include "Observer.h"


class Observee
{

public:
	//TODO revise this
	virtual bool registerObserver(std::shared_ptr<Observer> obs) = 0;
	virtual bool removeObserver(std::shared_ptr<Observer> obs) = 0;
	virtual bool notifyObservers() const = 0;

protected:
	//Observee();
	virtual ~Observee() {};

};

