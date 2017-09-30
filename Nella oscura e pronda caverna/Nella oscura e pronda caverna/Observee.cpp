#include "Observee.h"

bool Observee::registerObserver(Observer& obs)
{
	std::vector<Observer&>::iterator temp = find(observers.begin(), observers.end(), obs);
	//Return false if the observer is already in the vector. This is not expected. But there is nothing really wrong either
	if (temp != observers.end())
		return false;

	observers.push_back(obs);
	return true;
}

bool Observee::removeObserver(Observer& obs)
{
	std::vector<Observer&>::iterator temp = find(observers.begin(), observers.end(), obs);
	//Return false if the observer could not be found (and evidently can’t be removed.
	if (temp == observers.end())
		return false;
	else
		observers.erase(temp);
	return true;
}

bool Observee::notifyObservers() const
{
	for (std::vector<Observer&>::const_iterator i = observers.begin(); i != observers.end(); i++)
	{
		i->update(/*something*/);
	}
	return (observers.size() > 0);
}
