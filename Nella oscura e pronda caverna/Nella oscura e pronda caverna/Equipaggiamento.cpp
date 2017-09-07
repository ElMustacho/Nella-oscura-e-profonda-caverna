#include "Equipaggiamento.h"



Equipaggiamento::Equipaggiamento()
{
}


Equipaggiamento::~Equipaggiamento()
{
}
//TODO FIXME
bool Equipaggiamento::equipaggia(std::shared_ptr<Oggetto> toEquip)
{
	if (std::dynamic_pointer_cast<Arma>(toEquip) != nullptr) //È un'arma?
	{
		if (armaPrimaria.get() != nullptr) //Ho già un arma?
			return false; //Sì
		else
		{
			auto something = std::make_shared<Arma>(*toEquip);
			armaPrimaria = std::make_shared<Arma>(*toEquip);
			return true; //No, quindi la equipaggio
		}

	}
	else if (std::dynamic_pointer_cast<Armatura>(toEquip) != nullptr) //È un'armatura?
	{
		if (armatura.get() != nullptr) //Ho già un'armatura?
			return false; //Sì
		else
		{
			armatura = std::make_shared<Armatura>(*toEquip);
			return true; //No, quindi la equipaggio
		}
	}
	else { //Non è un oggetto che posso equipaggiare
		return false;
	}
}

std::shared_ptr<Oggetto> Equipaggiamento::disequip(int posizione)
{
	switch (posizione) {
	case 0:
		if (armaPrimaria != nullptr) {
			auto temp = std::make_shared<Arma>(*armaPrimaria);
			armaPrimaria.reset();
			return temp;
		}
		break;
	case 2:
		if (armatura != nullptr) {
			auto temp = std::make_shared<Armatura>(*armatura);
			armaPrimaria.reset();
			return temp;
		}
		break;
	default:
		return nullptr; // nulla da disequipaggiare
	}

}
