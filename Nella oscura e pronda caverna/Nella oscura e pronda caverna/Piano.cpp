#include <fstream>
#include <iostream>
#include <cmath>
#include <deque>
#include "Piano.h"


Piano::~Piano()
{
}

//Numeri minimi e numeri massimi vengono portati a 0 e la dimensione del piano rispettiva, rispettivamente (scusate il gioco di parole)
int Piano::posizione(int x, int y) {
	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	if (x >= larghezza)
		x = larghezza-1;
	if (y >= lunghezza)
		y = lunghezza-1;
	return x + y*larghezza;
}
//TODO
bool Piano::removeEntita(cood coodElimina) {
	return false;
}

void Piano::scontro(cood posizioneVittima, cood posizioneAttaccante)
{
	if (pavimento.at(posizione(posizioneAttaccante)).getEntita() == nullptr)
		return; //nessun attaccante
	auto danno = pavimento.at(posizione(posizioneAttaccante)).getEntita()->attacca();
	if (danno.getAmmontare() < 0)
		return; //nessun danno
	else
		scontro(posizioneVittima, danno);
}
void Piano::scontro(cood posizioneVittima, Danno dannoInflitto)
{
	if (pavimento.at(posizione(posizioneVittima)).getEntita().get() == nullptr)
		return; //nessun bersaglio
	else
		if(pavimento.at(posizione(posizioneVittima)).getEntita()->subisciDanno(dannoInflitto)){
			auto vPosizioni = getVectorPosizioni();
			auto it = std::find(vPosizioni.begin(), vPosizioni.end(), posizioneVittima);
			//HACK devo chiamare removeEntita
			entitaPresenti.erase(entitaPresenti.begin()+std::distance(vPosizioni.begin(),it));
			pavimento.at(posizione(posizioneVittima)).setEntita(nullptr);
	}
			return; //TODOFAR lascia inventario ed equipaggiamento per terra.
}
//Stesso funzionamento di Piano::posizione()
Casella & Piano::at(int x, int y) 
{ 
	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	if (x >= larghezza)
		x = larghezza-1;
	if (y >= lunghezza)
		y = lunghezza-1;
	return pavimento.at(x + y * larghezza); 
}

Casella & Piano::at(cood coord) {
	return at(coord.first, coord.second);
}

bool Piano::isCoodLegal(cood coord) {
	if (coord.first < 0 || coord.first >= larghezza || coord.second < 0 || coord.second >= lunghezza)
		return false;
	return true;
}

int Piano::posizione(cood coord) {
	return posizione(coord.first,coord.second);
}

cood Piano::fromPosizioneToInt(int x) {
	return cood(x % larghezza, x / larghezza);
}

bool Piano::popolaPiano()
{
	return false;
}

bool Piano::spargiLoot() 
{
	return false;
}

bool Piano::placeEntita(std::shared_ptr<Entita> placeMe, cood coord) //FIXME inserisco gente nelle pareti
{
	if (pavimento.at(posizione(coord)).getEntita() == nullptr) {
		pavimento.at(posizione(coord)).setEntita(placeMe);
		std::shared_ptr<Entita> copyTemp = placeMe;
		std::pair<std::shared_ptr<Entita>, cood> entitaTabella(copyTemp, coord);
		entitaPresenti.push_back(entitaTabella);
		return true;
	}
	else
	{
		return false;
	}
}

Piano::Piano() {

}

Piano::Piano(int larghezza, int lunghezza, std::vector<std::shared_ptr<Oggetto>> lootPossibile, std::vector<std::shared_ptr<Entita>> entitaPossibili)
{
}

bool Piano::creaStanzaRettangolare(int posX, int posY, int dimX, int dimY) 
{
	if (posX + dimX  > lunghezza || posY + dimY > larghezza)
		return false; //Stanza prodotta fuori dal piano
	
	for (int i = posX; i < dimX + posX; i++) 
	{
		for (int j = posY; j < dimY + posY; j++)
			if (!pavimento.at(posizione(i,j)).isMuro()) 
			{
				return false; //Spazio per stanza non trovato
			}
	}
	for (int i = posX; i < dimX + posX; i++) //CHECK Possibile con un ELSE evitare questo ciclo?
	{
		for (int j = posY; j < dimY + posY; j++)
		{
			pavimento.at(posizione(i, j)).Scava(); //Crea stanza
		}
	}
	return true;
}

bool Piano::creaPorte(int posX, int posY, int dimX, int dimY) //TODO Presa una stanza, prova a costruirci intorno delle porte
{
	return true;
}

std::vector<std::shared_ptr<Entita>> Piano::getVectorEntita() {
	std::vector<std::shared_ptr<Entita>> returned;
	for each (std::pair<std::shared_ptr<Entita>,cood> entity in entitaPresenti)
	{
		returned.push_back(entity.first);
	}
	return returned;
}

std::vector<cood> Piano::getVectorPosizioni() {
	std::vector<cood> returned;
	for each (std::pair<std::shared_ptr<Entita>, cood> entity in entitaPresenti)
	{
		returned.push_back(entity.second);
	}
	return returned;
}

std::vector<cood> Piano::floodFill(cood posizionePartenza)
{
	std::vector<cood> caselleOk{};
	caselleOk.reserve(lunghezza*larghezza);
	std::deque<cood> codaCaselle;
	auto casella = pavimento.at(posizione(posizionePartenza));
	if (casella.isMuro()) {
		return caselleOk;
	}
	codaCaselle.push_back(posizionePartenza);
	while (!codaCaselle.empty()) {
		auto casellaControllata = codaCaselle.front();
		codaCaselle.pop_front();
		if (!pavimento.at(posizione(casellaControllata)).isMuro()) {
			if (std::find(caselleOk.begin(), caselleOk.end(), casellaControllata) == caselleOk.end()) {
				caselleOk.push_back(casellaControllata);
				cood coordFF(casellaControllata.first+1, casellaControllata.second);
				if(isCoodLegal(coordFF))	
					codaCaselle.push_back(coordFF);
				coordFF.second++;
				if (isCoodLegal(coordFF))	
					codaCaselle.push_back(coordFF);
				coordFF.first--;
				if (isCoodLegal(coordFF))	
					codaCaselle.push_back(coordFF);
				coordFF.first--;
				if (isCoodLegal(coordFF))	
					codaCaselle.push_back(coordFF);
				coordFF.second--;
				if (isCoodLegal(coordFF))	
					codaCaselle.push_back(coordFF);
				coordFF.second--;
				if (isCoodLegal(coordFF))	
					codaCaselle.push_back(coordFF);
				coordFF.first++;
				if (isCoodLegal(coordFF))	
					codaCaselle.push_back(coordFF);
				coordFF.first++;
				if (isCoodLegal(coordFF))	
					codaCaselle.push_back(coordFF);
			}
		}
	}
	return caselleOk;
}

//TODOFAR il carattere stampato deve essere restituito dalla casella tramite una sua funzione
void Piano::StampaChar() 
{ 
	std::string mappa="";
	for (unsigned int i = 0; i < pavimento.size(); i++)

	{
		auto casella = pavimento.at(i);
		auto entity = casella.getEntita();
		if (casella.isMuro())
			mappa.push_back('#');
		//else if (dynamic_cast<Protagonista*>(entity.get()) != NULL) //LOOKATME così si prende il tipo di puntatore shared ptr
		//	mappa.push_back('@');
		else if (std::dynamic_pointer_cast<Protagonista>(entity) != nullptr)
			mappa.push_back('@');
		else if (dynamic_cast<Attore*>(entity.get()) != NULL)
			mappa.push_back('*');
		else if (!casella.getOggetti().empty())
			mappa.push_back(casella.getOggetti().front()->getNome().front()); //Il primo carattere del nome dell'oggetto in cima alla lista
		else if (casella.getEvento() == 1) 
			mappa.push_back('>');//Scale
		else
			mappa.push_back('.');
		if ((i + 1) % larghezza == 0)
			mappa.push_back('\n');
	}
	std::cout << mappa;
}

int Piano::muoviEntita(int posX, int posY, int targetX, int targetY) //I primi due sono quelli da dove parto, gli altri dove arrivo
{
	if (pavimento.at(posizione(posX, posY)).getEntita() == NULL) 
	{
		return -1; //Qui non c'è nessuno
	}
	if (posX == targetX && posY == targetY) //Questo significa non spostarsi per davvero
	{
		return -2;
	}
	if (!(targetX > -1 && targetX<larghezza && targetY>-1 && targetY < lunghezza))
	{
		return -3; //Posizione non valida per almeno una delle coordinate
	}

	int distanza, metodo;
	pavimento.at(posizione(posX, posY)).getEntita()->muovi(distanza,metodo);

	if (distanza == 0)
	{
		return -4; //Ho provato a muovermi ma sono immobile
	}

	//TODO Dijkstra per determinare la direzione da percorrere (qualora sia necessario usarlo).
	//Qui sotto il sistema di spostamento è stupido, ma potrebbe funzionare per gestire entità prive di intelligenza
	//tipo qualche golem, melma, zombie o goblin ubriaco fradicio. In pratica non verifico la validità finale del percorso,
	//ma solo quella della casella in cui mi voglio spostare, una per volta.
	//P.S. questo sistema funziona bene anche quando c'è solo una casella da percorrere.

	//FIXME da qui assumo che il movimento sia in linea retta
	while (distanza != 0 && !(posX == targetX && posY == targetY)) //Esco quando ho terminato i movimenti o quando sono arrivato.
	{ 
		int moveX=0, moveY=0;
		if (posX < targetX)
		{
			moveX = 1;
		}
		else if (posX > targetX)
		{
			moveX = -1;
		}
		else {}

		if (posY < targetY)
		{
			moveY = 1;
		}
		else if (posY > targetY)
		{
			moveY = -1;
		}
		else {}
		
		//Qui l'unico controllo presente è che la casella non sia un muro e che nella casella non ci sia nessuno.
		if (pavimento.at(posizione(posX + moveX, posY + moveY)).isMuro()) //Qui c'è un muro
		{  
			return 1;
		}
		else if (pavimento.at(posizione(posX + moveX, posY + moveY)).getEntita() != NULL) //Qui c'è qualcun'altro
		{
			return 2;
		}
		else //Date le premesse, spostarsi è sicuro e valido
		{ 
			std::shared_ptr<Entita> temp = pavimento.at(posizione(posX, posY)).getEntita();
			pavimento.at(posizione(posX, posY)).setEntita(nullptr);
			pavimento.at(posizione(posX + moveX, posY + moveY)).setEntita(temp);
			//TODOFAR fammi funzionare al posto delle 3 istruzioni percedenti
			//pavimento.at(posizione(posX, posY)).getEntita().swap(pavimento.at(posizione(posX + moveX, posY + moveY)).getEntita());
			cood coordinatePrima(posX, posY);
			posX += moveX;
			posY += moveY;
			distanza--;
			cood coordinateDopo(posX, posY);
			auto vPosizioni = getVectorPosizioni();
			auto it = std::find(vPosizioni.begin(), vPosizioni.end(), coordinatePrima);
			if (it != vPosizioni.end()) {
				auto distanza = std::distance(vPosizioni.begin(), it);
				entitaPresenti[distanza].second = coordinateDopo;
			}
			pavimento.at(posizione(posX, posY)).doEvento();
		}
	}
	if (distanza == 0 && (posX == targetX && posY == targetY))
	{
		return 0; //sono arrivato precisamente a destinazione
	}
	else if (distanza != 0 && (posX == targetX && posY == targetY))
	{
		return 3; //sono arrivato a destinazione ma avevo movimento avanzato
	}
	else
	{
		return 4; //non sono arrivato a destinazione perché ho finito il movimento
	}
}
//TODOFAR il carattere stampato deve essere restituito dalla casella tramite una sua funzione
void Piano::StampaFileChar() 
{
	std::ofstream file ("mappa.map");
	for (int i = 0; i < lunghezza*larghezza; i++)
	{
		auto casella = pavimento.at(i);
		auto entity = casella.getEntita();
		//Per ora l'ordine va bene così, ma non è detto che in un muro non ci possano essere nemici (tipo fantasmi)
		//FIXME dev'essere come l'altra stampa
		if (dynamic_cast<Protagonista*>((&entity)->get()) != NULL) //se entity è NULL il dynamic cast risponde NULL
		{
			file << '@';
		}
		else if (casella.isMuro()) //se entity è NULL il dynamic cast risponde NULL
		{
			file << '#';
		}
		else if (dynamic_cast<Attore*>((&entity)->get()) != NULL) //Same
		{
			file << '*';
		}
		else
		{
			file << '.';
		}
		if ((i + 1) % lunghezza == 0)
		{
			file << std::endl;
		}
	}
	file.close();
}
//TODO
std::shared_ptr<Entita> Piano::entityFactory(std::string)
{
	return nullptr;
}
//Lasciare vuoto per avere un personaggio principale, oppure mandare 0. Di default non rende nulla
std::shared_ptr<Entita> Piano::entityFactory(int codiceID)
{
	std::shared_ptr<Entita> appoggio;
	switch (codiceID) {
	case 0: {
		//TODO qui ovviamente dovrà esserci il modo di caricare un personaggio preesistente o di invocare il creatore di personaggi, per ora lo tratto come un qualunque idiota
		std::list<std::shared_ptr<Oggetto>> inventario{ std::shared_ptr<Oggetto> (new Oggetto(0.5, "Sfera di metallo", "Direi piuttosto che si tratta di un oggetto a forma d'uovo", 2)) };
		Attributi nellaMedia(4, 4, 4, 4, 4, 4, 4, 4);
		std::vector<std::shared_ptr<Oggetto>> equipaggiamento; //Picche, non hai nulla scemo
		appoggio = std::make_shared<Protagonista>(Protagonista("Medioman", inventario, nellaMedia, equipaggiamento, 1, 0, 0));
		break;
	}
	case 1:
	{// Goblin scrauso, puzzone e nudo
		std::list<std::shared_ptr<Oggetto>> inventario;
		Attributi scarso(3, 4, 2, 2, 2, 1, 3, 1);
		std::vector<std::shared_ptr<Oggetto>> equipaggiamento; //Picche, non hai nulla scemo puzzone
		appoggio = std::make_shared<Attore>("Goblin puzzone", inventario, scarso, equipaggiamento,1.1);
		break;
	}
	default:
	{
		appoggio = nullptr;
	}
	
	}
	return appoggio;
}
//TODO
std::shared_ptr<Oggetto> Piano::objectFactory(std::string nome)
{
	return std::shared_ptr<Oggetto>();
}
//default sfera di metallo
std::shared_ptr<Oggetto> Piano::objectFactory(int codiceID)
{
	std::shared_ptr<Oggetto> oggetto;
	switch (codiceID) {
	case 0: {
		oggetto = std::make_shared<Oggetto>(1,"Sfera di metallo","L'inutilita' fatta lucida.",0);
		break;
	}
	case 1: {
		oggetto = std::make_shared<Oggetto>(4, "Lingotto d'oro", "Incise sopra vi sono 24 carote", 2000);
		break;
	}
	case 2: {
		oggetto = std::make_shared<Arma>(2, "Spada normale", "Quando l'eroe parte all'avventura, se ha una spada ebbene e' questa", 15, Danno({ 1 }, 10));
		break;
	}
	case 3: {
		oggetto = std::make_shared<Oggetto>(0.25,"Fermaporte","Non particolarmente utile qui",4);
		break;
	}
	case 4: {
		oggetto = std::make_shared<Arma>(3, "Cannone laser automatico", "No kill like overkill", 4500, Danno({ 0,0,0,0.5,0.5 }, 600));
		break;
	}
	}
	return oggetto;
}
