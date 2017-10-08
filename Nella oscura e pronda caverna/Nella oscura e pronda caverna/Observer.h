#pragma once
class Observer
{
public:
	Observer();
	virtual ~Observer();
	virtual void update(double a, double b, double c) = 0;
	virtual void updateLevel(int livello)=0;
};

