#pragma once
class DisplayElement
{
public:

	virtual void display() const = 0;

protected:

	virtual ~DisplayElement() = 0 {};
};

