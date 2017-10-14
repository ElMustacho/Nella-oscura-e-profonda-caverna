#pragma once
#include <memory>
#include "Attore.h"
#include <random>
class MonsterFactory
{
public:
	static std::shared_ptr<Entita> makeMonRand(int code=-1);
	MonsterFactory(std::vector<std::shared_ptr<Entita>> entitaPossibili);
	void setMonsterList(std::vector<std::shared_ptr<Entita>> entitaPossibili);
	std::shared_ptr<Entita> makeMon(int code = -1);
	MonsterFactory();
	~MonsterFactory();
private:
	std::vector<std::shared_ptr<Entita>> entita;
};

