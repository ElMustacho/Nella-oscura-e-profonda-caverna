#pragma once
#include <vector>
#include <algorithm>

#include "Observer.h"


class Observee
{

public:
	~Observee();

	//TODO revise this
	virtual bool registerObserver(Observer& obs) = 0;
	virtual bool removeObserver(Observer& obs) = 0;
	virtual bool notifyObservers() const = 0;

protected:
	Observee();

private:
	std::vector<Observer&> observers;
	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	Observee(const Observee& ref);
	Observee& operator=(const Observee& ref);
};

