#pragma once

class Observer
{

public:
	virtual ~Observer();
	virtual void update() = 0;

protected:
	Observer() {};

private:
	
	Observer(const Observer& ref);
	Observer& operator=(const Observer& ref);
};

