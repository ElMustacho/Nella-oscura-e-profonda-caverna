#include "Casella.h"
#include "Scrigno.h"

Casella::Casella(Tileset tileset, Oggetto* oggetto, Entita* entità, bool trasparenza, bool attraversabile, int evento)
{
	this->tileset = tileset;
	this->oggetto = oggetto;
	this->entita = entità;
	this->trasparenza = trasparenza;
	this->attraversabile = attraversabile;
	this->evento = evento;
}

//Costruttore rapido e semplice, passare false per parete, passare true per terreno attraversabile
Casella::Casella(bool default) {
	tileset = Tileset(); //FIX ME quando Tileset avrà senso questo dovrà essere qualcosa di concreto.
	oggetto = NULL; //Non c'è nulla di default;
	entita = NULL; //Non c'è nessuno di defalut;
	trasparenza = default; //Se è una parete non è trasparente
	attraversabile = default; //Se è una parete non è attraversabile
	evento = 0; //Di default non accade nulla
}

bool Casella::isMuro()
{
	if (!attraversabile)
		if(!trasparenza)
			return true;
	return false;
}

void Casella::setOggetto(Oggetto * obj) //CHECK gestire la sovrapposizione degli oggetti
{
	if (this->oggetto != NULL)
	{
		if ((Scrigno*)(this->oggetto))
		{
			((Scrigno*)(this->oggetto))->inserisciOggetto(obj);
		}
		else
		{
			// crea scrigno fittizio
			std::list<Oggetto> loot;
			Scrigno mucchio(0, "Mucchio", "Gruppo di oggetti", 0, 0, loot);
			// inserisce l'oggetto già esistente e quello da inserire
			mucchio.inserisciOggetto(this->getOggetto());
			mucchio.inserisciOggetto(obj);
			// posiziona lo scrigno sulla casella
			this->setOggetto(&mucchio);
		}
	}
	else
	{
		this->oggetto = obj;
	}
}

bool Casella::setEntita(Entita * entity) //TODO gestire la sovrapposizione delle entità, avremo memory leak se cancelliamo la precedente!
{
	if (this->isMuro()) //Quando avremo entità incorporee questo if dovrà essere alterato
		return false;
	this->entita = entity;
	return true;
}

void Casella::doEvento()//FIXME sono un segnaposto
{

}

Casella::~Casella() //Se non libero questi puntatori non lo farà nessuno, PERÒ nessuno mi garantisce che io non preservi
					//cose importanti
{
	//delete (oggetto);
	//delete (entita);
}

void Casella::Scava() { //per scavare un muro in modo rapido
	tileset = Tileset(); //Da muro a pavimento
	trasparenza = true;
	attraversabile = true;
}