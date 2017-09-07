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
	if (std::dynamic_pointer_cast<Arma>(toEquip) != nullptr) //� un'arma?
	{
		if (armaPrimaria.get() != nullptr) //Ho gi� un arma?
			return false; //S�
		else
		{
			auto something = std::make_shared<Arma>(*toEquip);
			armaPrimaria = std::make_shared<Arma>(*toEquip);
			return true; //No, quindi la equipaggio
		}

	}
	else if (std::dynamic_pointer_cast<Armatura>(toEquip) != nullptr) //� un'armatura?
	{
		if (armatura.get() != nullptr) //Ho gi� un'armatura?
			return false; //S�
		else
		{
			armatura = std::make_shared<Armatura>(*toEquip);
			return true; //No, quindi la equipaggio
		}
	}
	else { //Non � un oggetto che posso equipaggiare
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
