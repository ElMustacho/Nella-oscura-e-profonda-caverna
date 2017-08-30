#include <fstream>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <typeinfo>

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
			pavimento.at(posizione(posizioneVittima)).drop();
			pavimento.at(posizione(posizioneVittima)).setEntita(nullptr);
	}
			return; //TODOFAR lascia equipaggiamento per terra.
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
		turni.push_back(*placeMe);
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
	for (int i = posX; i < dimX + posX; i++) //LOOKATME Possibile con un ELSE evitare questo ciclo?
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
			mappa.push_back('>'); //Scale
		else
			mappa.push_back('.');
		if ((i + 1) % larghezza == 0)
			mappa.push_back('\n');
	}
	std::cout << mappa;
}

cood Piano::getPositionOfPlayer()
{
	return entitaPresenti.begin()->second;
}

// Diagonal distance
double heuristic(int posX, int posY, int targetX, int targetY)
{
	// Version: Octile distance
	auto dx = abs(posX - targetX);
	auto dy = abs(posY - targetY);
	auto normalCost = 1;
	auto diagonalCost = sqrt(2);

	return normalCost * (dx + dy) + (diagonalCost - 2 * normalCost) * std::min(dx, dy);
};

double heuristic(coord pos, coord target)
{
	return heuristic(pos.first, pos.second, target.first, target.second);
}

//TODO x e y sono invertiti
int Piano::muoviEntita(int posX, int posY, int targetX, int targetY) //I primi due sono quelli da dove parto, gli altri dove arrivo
{
	coord pos(posX, posY);
	coord target(targetX, targetY);

	if ( pavimento.at( posizione(pos) ).getEntita() == nullptr )
	{
		return -1; //Qui non c'è nessuno
	}
	if ( pos == target ) //Questo significa non spostarsi per davvero
	{
		return -2;
	}
	if ( !(target.first > -1 && target.first < lunghezza && target.second > -1 && target.second < larghezza) )
	{
		return -3; //Posizione non valida per almeno una delle coordinate
	}

	int distanza, metodo;
	pavimento.at( posizione(pos) ).getEntita()->muovi(distanza, metodo);
	
	if (distanza == 0)
	{
		return -4; //Ho provato a muovermi ma sono immobile
	}

	// CHECK A* (Dijkstra + heuristic) per determinare la direzione da percorrere (qualora sia necessario usarlo).
	//Qui sotto il sistema di spostamento è stupido, ma potrebbe funzionare per gestire entità prive di intelligenza
	//tipo qualche golem, melma, zombie o goblin ubriaco fradicio. In pratica non verifico la validità finale del percorso,
	//ma solo quella della casella in cui mi voglio spostare, una per volta.
	//P.S. questo sistema funziona bene anche quando c'è solo una casella da percorrere.
	
	if ( typeid( *(pavimento.at(posizione(pos)).getEntita()) ) != typeid(Protagonista) )
	{
		/* TENTATIVO STIMA DISTANZA (con heuristic) */
		distanza = heuristic(pos, target);

		return aStar(pos, target, distanza, metodo);
	}
	else
	{
		//FIXME da qui assumo che il movimento sia in linea retta
		while ( distanza != 0 && !(pos == target) ) //Esco quando ho terminato i movimenti o quando sono arrivato.
		{
			int moveX = 0, moveY = 0;

			if (pos.first < target.first)
			{
				moveX = 1;
			}
			else if (pos.first > target.first)
			{
				moveX = -1;
			}
			else {}

			if (pos.second < target.second)
			{
				moveY = 1;
			}
			else if (pos.second > target.second)
			{
				moveY = -1;
			}
			else 
			{
			}

			coord updatePos(pos.first + moveX, pos.second + moveY);

			//Qui l'unico controllo presente è che la casella non sia un muro e che nella casella non ci sia nessuno.
			if ( pavimento.at( posizione(updatePos) ).isMuro() ) //Qui c'è un muro
			{
				return 1;
			}
			else if ( pavimento.at( posizione(updatePos) ).getEntita() != nullptr ) //Qui c'è qualcun'altro
			{
				return 2;
			}
			else //Date le premesse, spostarsi è sicuro e valido
			{
				std::shared_ptr<Entita> temp = pavimento.at( posizione(pos) ).getEntita();
				pavimento.at( posizione(pos) ).setEntita(nullptr);
				pavimento.at( posizione(pos.first + moveX, pos.second + moveY) ).setEntita(temp);
				pos.first += moveX;
				pos.second += moveY;
				pavimento.at( posizione(pos) ).doEvento();
				distanza--;
			}
		}
		if ( distanza == 0 && (pos == target) )
		{
			return 0; //sono arrivato precisamente a destinazione
		}
		else if ( distanza != 0 && (pos == target) )
		{
			return 3; //sono arrivato a destinazione ma avevo movimento avanzato
		}
		else
		{
			return 4; //non sono arrivato a destinazione perché ho finito il movimento
		}
		
	}


}

//TODOFAR il carattere stampato deve essere restituito dalla casella tramite una sua funzione


int Piano::muoviEntita(coord pos, coord target) //I primi due sono quelli da dove parto, gli altri dove arrivo
{
	return muoviEntita(pos.first, pos.second, target.first, target.second);
}


void Piano::checkSuccessor(coord pos, coord target, coord check, std::string direct, bool &destination, node &q, std::vector<node> &openList, std::vector<node> &closedList)
{
	// Costs
	auto normalCost = 1;
	auto diagonalCost = sqrt(2);
	auto objectCost = 0.5;

	if (!destination && !pavimento.at(posizione(check)).isMuro() && !pavimento.at(posizione(check)).hasTrap() && pavimento.at(posizione(check)).getEntita() == nullptr)
	{
		double gNew = q.g;

		if ( direct.compare("nord") == 0 || direct.compare("sud") == 0 || direct.compare("est") == 0 || direct.compare("ovest") == 0)
		{
			gNew += normalCost;
		}
		else if (direct.compare("nordEst") == 0 || direct.compare("nordOvest") == 0 || direct.compare("sudEst") == 0 || direct.compare("sudOvest") == 0 )
		{
			gNew += diagonalCost;
		}
		if (pavimento.at(posizione(check)).getOggetti().size() != 0)
		{
			gNew += objectCost;
		}

		double hNew = heuristic(check, target);
		double fNew = gNew + hNew;

		struct node direction;
		direction.posX = check.first;
		direction.posY = check.second;
		direction.g = gNew;
		direction.h = hNew;
		direction.f = fNew;
		direction.parentX = q.posX;
		direction.parentY = q.posY;

		// if is destination
		if (check == target)
		{
			closedList.push_back(q);
			closedList.push_back(direction);
			destination = true;
		}
		else
		{
			bool found = false;
			bool minus = false;

			// looking for this node in closedList
			for (std::vector<node>::iterator i = closedList.begin(); i < closedList.end(); i++)
			{
				if (i->posX == direction.posX && i->posY == direction.posY && i->f < fNew)
				{
					found = true;
					break;
				}
			}

			if (!found)
			{
				//CHECK looking for this node in openList
				for (std::vector<node>::iterator i = openList.begin(); i < openList.end(); i++)
				{
					if (i->posX == direction.posX && i->posY == direction.posY)
					{
						found = true;
						if (i->f > fNew)
							minus = true;
						break;
					}
				}

				if (!found || (found && minus))
				{
					openList.push_back(direction);
				}
			}

		}

	}
}


int Piano::aStar(coord pos, coord target, int distanza, int metodo)
{
	
	std::vector<node> openList;
	std::vector<node> closedList;
	bool destination = false;
	auto beginHeuristic = heuristic(pos, target);

	struct node startingNode(pos.first, pos.second, pos.first, pos.second, beginHeuristic, 0, beginHeuristic);
	openList.push_back(startingNode);

	while (!openList.empty() && !destination)
	{
		double min = DBL_MAX;
		std::vector<node>::iterator position;
		struct node q;

		// find the min 'f' node in openList
		for (std::vector<node>::iterator i = openList.begin(); i < openList.end(); i++)
		{
			if (i->f < min)
			{
				min = i->f;
				position = i;
			}
		}
		// Save the node and erase it from openList
		q = *position;
		openList.erase(position);

		/* Generates 8 successors (nearby cells) */

		//----------- 1st Successor North (x, y-1) ------------

		coord nord(q.posX, q.posY - 1);
		checkSuccessor(pos, target, nord, "nord",destination, q, openList, closedList);

		//----------- 2nd Successor South (x, y+1) ------------

		coord sud(q.posX, q.posY + 1);
		checkSuccessor(pos, target, sud, "sud",destination, q, openList, closedList);

		//----------- 3rd Successor East (x+1, y) ------------

		coord est(q.posX + 1, q.posY);
		checkSuccessor(pos, target, est, "est",destination, q, openList, closedList);

		//----------- 4th Successor West (x-1, y) ------------

		coord ovest(q.posX - 1, q.posY);
		checkSuccessor(pos, target, ovest, "ovest",destination, q, openList, closedList);

		//----------- 5th Successor North-East (x+1, y-1) ------------

		coord nordEst(q.posX + 1, q.posY - 1);
		checkSuccessor(pos, target, nordEst, "nordEst",destination, q, openList, closedList);

		//----------- 6th Successor North-West (x-1, y-1) ------------

		coord nordOvest(q.posX - 1, q.posY - 1);
		checkSuccessor(pos, target, nordOvest, "nordOvest", destination, q, openList, closedList);

		//----------- 7th Successor South-East (x+1, y+1) ------------

		coord sudEst(q.posX + 1, q.posY + 1);
		checkSuccessor(pos, target, sudEst, "sudEst", destination, q, openList, closedList);

		//----------- 8th Successor South-West (x-1, y+1) ------------

		coord sudOvest(q.posX - 1, q.posY + 1);
		checkSuccessor(pos, target, sudOvest, "sudOvest", destination, q, openList, closedList);
		
		if (!destination)
		{
			// Push q on the closedList
			closedList.push_back(q);
		}

	}

	for (std::vector<node>::iterator i = closedList.begin(); i < closedList.end() && distanza > 0; i++)
	{
		std::cout << "( " << i->posX << ", " << i->posY << " ) -> " << i->f << std::endl;
		
		//TODO muovi enita
		pos.first = i->posX;
		pos.second = i->posY;
		coord next( (i + 1)->posX, (i + 1)->posY );

		std::shared_ptr<Entita> temp = pavimento.at( posizione(pos) ).getEntita();
		pavimento.at( posizione(pos) ).setEntita(nullptr);
		pavimento.at( posizione(next) ).setEntita(temp);
		
		pavimento.at( posizione(next) ).doEvento();
		distanza--;

	}

	//CHECK Arrivato?
	if (distanza == 0 && (pos == target))
	{
		return 0; //sono arrivato precisamente a destinazione
	}
	else if (distanza != 0 && (pos == target))
	{
		return 3; //sono arrivato a destinazione ma avevo movimento avanzato
	}
	else
	{
		return 4; //non sono arrivato a destinazione perché ho finito il movimento
	}

}


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

