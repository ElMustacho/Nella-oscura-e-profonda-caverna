#pragma once
#include <memory>
#include "Attore.h"
#include <random>
class MonsterFactory
{
public:
	static std::shared_ptr<Entita> makeMon(int code=-1);
	MonsterFactory();
	~MonsterFactory();
};

