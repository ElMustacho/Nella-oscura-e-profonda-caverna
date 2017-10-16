#pragma once
class Subject
{
public:
	Subject();
	virtual ~Subject();
	virtual void update()=0;
};

