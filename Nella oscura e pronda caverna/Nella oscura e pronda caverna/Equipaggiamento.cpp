#include "Equipaggiamento.h"



Equipaggiamento::Equipaggiamento()
{
}


Equipaggiamento::~Equipaggiamento()
{
}
//TODO aggiungere funzione a parte per equipaggiare qualsiasi oggetto come arma

//Questa funzione mette a posto da sola gli oggetti che vengono passati, se pu� farlo
bool Equipaggiamento::equipaggia(std::shared_ptr<Oggetto> toEquip)
{
	if (std::dynamic_pointer_cast<Arma>(toEquip) != nullptr) //� un'arma?
	{
		if (armaPrimaria.get() != nullptr) //Ho gi� un arma?
			return false; //S�
		else
		{
			armaPrimaria = std::dynamic_pointer_cast<Arma>(toEquip);
			return true; //No, quindi la equipaggio
		}

	}
	else if (std::dynamic_pointer_cast<Armatura>(toEquip) != nullptr) //� un'armatura?
	{
		if (armatura.get() != nullptr) //Ho gi� un'armatura?
			return false; //S�
		else
		{
			armatura = std::dynamic_pointer_cast<Armatura>(toEquip);
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
