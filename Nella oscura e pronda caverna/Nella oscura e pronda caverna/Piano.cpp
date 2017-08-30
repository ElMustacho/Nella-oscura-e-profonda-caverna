#include <fstream>
#include <iostream>
#include <cmath>
#include <deque>
#include <algorithm>
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
		x = larghezza - 1;
	if (y >= lunghezza)
		y = lunghezza - 1;
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
		if (pavimento.at(posizione(posizioneVittima)).getEntita()->subisciDanno(dannoInflitto)) {
			auto vPosizioni = getVectorPosizioni();
			auto it = std::find(vPosizioni.begin(), vPosizioni.end(), posizioneVittima);
			//HACK devo chiamare removeEntita
			entitaPresenti.erase(entitaPresenti.begin() + std::distance(vPosizioni.begin(), it));
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
		x = larghezza - 1;
	if (y >= lunghezza)
		y = lunghezza - 1;
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
	return posizione(coord.first, coord.second);
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
			if (!pavimento.at(posizione(i, j)).isMuro())
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
	for each (std::pair<std::shared_ptr<Entita>, cood> entity in entitaPresenti)
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
				cood coordFF(casellaControllata.first + 1, casellaControllata.second);
				if (isCoodLegal(coordFF))
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
	std::string mappa = "";
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

double heuristic(coord pos, coord target) {
	return heuristic(pos.first, pos.second, target.first, target.second);
}


cood Piano::getPositionOfEntity(std::shared_ptr<Entita> entita)
{
	auto vect = getVectorEntita();
	auto it = std::find(vect.begin(), vect.end(), entita);
	if (it == vect.end())
		return cood(-1, -1);
	else {
		auto posizione = *(getVectorPosizioni().begin() + (std::distance(vect.begin(), it)));
		return posizione;
	}
}

int Piano::muoviEntita(int posX, int posY, int targetX, int targetY) //I primi due sono quelli da dove parto, gli altri dove arrivo
{
	if (pavimento.at(posizione(posX, posY)).getEntita() == nullptr) // CHECK Dovrebbe essere nullptr, no?
	{
		return -1; //Qui non c'è nessuno
				   //FIXME ordine sbagliato
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
	pavimento.at(posizione(posX, posY)).getEntita()->muovi(distanza, metodo);
	/* TENTATIVO STIMA DISTANZA (con heuristic) */
	//distanza = heuristic(posX, posY, targetX, targetY);

	if (distanza == 0)
	{
		return -4; //Ho provato a muovermi ma sono immobile
	}

	// TODO A* (Dijkstra + heuristic) per determinare la direzione da percorrere (qualora sia necessario usarlo).
	//Qui sotto il sistema di spostamento è stupido, ma potrebbe funzionare per gestire entità prive di intelligenza
	//tipo qualche golem, melma, zombie o goblin ubriaco fradicio. In pratica non verifico la validità finale del percorso,
	//ma solo quella della casella in cui mi voglio spostare, una per volta.
	//P.S. questo sistema funziona bene anche quando c'è solo una casella da percorrere.

	coord pos(posX, posY);
	coord target(targetX, targetY);

	aStar(pos, target);

	//FIXME da qui assumo che il movimento sia in linea retta
	while (distanza != 0 && !(posX == targetX && posY == targetY)) //Esco quando ho terminato i movimenti o quando sono arrivato.
	{
		int moveX = 0, moveY = 0;
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



int Piano::muoviEntita(coord pos, coord target) //I primi due sono quelli da dove parto, gli altri dove arrivo
{
	return muoviEntita(pos.first, pos.second, target.first, target.second);
}


void Piano::aStar(coord pos, coord target)
{
	/* A* Algorithm */
	/////////////////////////////

	// CHECK Aumento costo se oggetto su casella
	// CHECK Comportamento se Entita su Casella
	// DOUBT Scrivere metodo checkSuccessor(coord pos) ???
	// CHECK Implementa posizione(coord xy)
	// CHECK Implementa muoviEntita(coord pod, coord target)

	struct node
	{
		node() {}
		node(int posX, int posY, int parentX, int parentY, double f, double g, double h)
		{
			this->posX = posX;
			this->posY = posY;

			this->parentX = parentX;
			this->parentY = parentY;

			this->f = f; // movement cost + heuristic 
			this->g = g; // movement cost
			this->h = h; // heuristic
		}
		int posX, posY;
		int parentX, parentY;
		double f, g, h;
	};


	std::vector<node> openList;
	std::vector<node> closedList;
	bool destination = false;

	// Costs
	auto normalCost = 1;
	auto diagonalCost = sqrt(2);
	auto objectCost = 0.5;

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

		if (!destination && !pavimento.at(posizione(nord)).isMuro() && !pavimento.at(posizione(nord)).hasTrap() && pavimento.at(posizione(nord)).getEntita() != nullptr)
		{

			double gNew = q.g + normalCost;
			if (pavimento.at(posizione(nord)).getOggetti().size() != 0)
			{
				gNew += objectCost;
			}

			double hNew = heuristic(nord, target);
			double fNew = gNew + hNew;

			// if is destination
			if (nord == target)
			{
				struct node north;
				north.posX = q.posX;
				north.posY = q.posY - 1;
				north.g = gNew;
				north.h = hNew;
				north.f = fNew;
				north.parentX = q.posX;
				north.parentY = q.posY;

				closedList.push_back(q);
				closedList.push_back(north);
				destination = true;
			}
			else
			{
				bool found = false;
				bool minus = false;

				// looking for this node in closedList
				for (std::vector<node>::iterator i = closedList.begin(); i < closedList.end(); i++)
				{
					if (i->posX == q.posX && i->posY == q.posY - 1 && i->f < fNew)
					{
						found = true;
						break;
					}
				}

				if (!found)
				{
					// looking for this node in openList
					for (std::vector<node>::iterator i = openList.begin(); i < openList.end(); i++)
					{
						if (i->posX == q.posX && i->posY == q.posY - 1)
						{
							found = true;
							if (i->f > fNew)
								minus = true;
							break;
						}
					}

					if (!found || (found && minus))
					{
						struct node north;
						north.posX = q.posX;
						north.posY = q.posY - 1;
						north.g = gNew;
						north.h = hNew;
						north.f = fNew;
						north.parentX = q.posX;
						north.parentY = q.posY;

						openList.push_back(north);
					}
				}

			}

		}

		//----------- 2nd Successor South (x, y+1) ------------

		coord sud(q.posX, q.posY + 1);

		if (!destination && !pavimento.at(posizione(sud)).isMuro() && !pavimento.at(posizione(sud)).hasTrap() && pavimento.at(posizione(nord)).getEntita() != nullptr)
		{

			double gNew = q.g + normalCost;
			if (pavimento.at(posizione(sud)).getOggetti().size() != 0)
			{
				gNew += objectCost;
			}

			double hNew = heuristic(sud, target);
			double fNew = gNew + hNew;

			// if is destination
			if (sud == target)
			{
				struct node south;
				south.posX = pos.first;
				south.posY = pos.second;
				south.g = gNew;
				south.h = hNew;
				south.f = fNew;
				south.parentX = q.posX;
				south.parentY = q.posY;

				closedList.push_back(q);
				closedList.push_back(south);
				destination = true;
			}
			else
			{
				bool found = false;
				bool minus = false;

				// looking for this node in closedList
				for (std::vector<node>::iterator i = closedList.begin(); i<closedList.end(); i++)
				{
					if (i->posX == q.posX && i->posY == q.posY + 1)
					{
						found = true;
						break;
					}
				}

				if (!found)
				{
					// looking for this node in openList
					for (std::vector<node>::iterator i = openList.begin(); i<openList.end(); i++)
					{
						if (i->posX == q.posX && i->posY == q.posY + 1)
						{
							found = true;
							if (i->f > fNew)
								minus = true;
							break;
						}
					}

					if (!found || (found && minus))
					{
						struct node south;
						south.posX = q.posX;
						south.posY = q.posY + 1;
						south.g = gNew;
						south.h = hNew;
						south.f = fNew;
						south.parentX = q.posX;
						south.parentY = q.posY;

						openList.push_back(south);
					}
				}

			}

		}

		//----------- 3rd Successor East (x+1, y) ------------

		coord est(q.posX + 1, q.posY);

		if (!destination && !pavimento.at(posizione(est)).isMuro() && !pavimento.at(posizione(est)).hasTrap() && pavimento.at(posizione(nord)).getEntita() != nullptr)
		{

			double gNew = q.g + normalCost;
			if (pavimento.at(posizione(est)).getOggetti().size() != 0)
			{
				gNew += objectCost;
			}

			double hNew = heuristic(est, target);
			double fNew = gNew + hNew;

			// if is destination
			if (est == target)
			{
				struct node east;
				east.posX = q.posX + 1;
				east.posY = q.posY;
				east.g = gNew;
				east.h = hNew;
				east.f = fNew;
				east.parentX = q.posX;
				east.parentY = q.posY;

				closedList.push_back(q);
				closedList.push_back(east);
				destination = true;
			}
			else
			{
				bool found = false;
				bool minus = false;

				// looking for this node in closedList
				for (std::vector<node>::iterator i = closedList.begin(); i<closedList.end(); i++)
				{
					if (i->posX == q.posX + 1 && i->posY == q.posY)
					{
						found = true;
						break;
					}
				}

				if (!found)
				{
					// looking for this node in openList
					for (std::vector<node>::iterator i = openList.begin(); i<openList.end(); i++)
					{
						if (i->posX == q.posX + 1 && i->posY == q.posY)
						{
							found = true;
							if (i->f > fNew)
								minus = true;
							break;
						}
					}

					if (!found || (found && minus))
					{
						struct node east;
						east.posX = q.posX + 1;
						east.posY = q.posY;
						east.g = gNew;
						east.h = hNew;
						east.f = fNew;
						east.parentX = q.posX;
						east.parentY = q.posY;

						openList.push_back(east);
					}
				}

			}

		}

		//----------- 4th Successor West (x-1, y) ------------

		coord ovest(q.posX - 1, q.posY);

		if (!destination && !pavimento.at(posizione(ovest)).isMuro() && !pavimento.at(posizione(ovest)).hasTrap() && pavimento.at(posizione(nord)).getEntita() != nullptr)
		{

			double gNew = q.g + normalCost;
			if (pavimento.at(posizione(ovest)).getOggetti().size() != 0)
			{
				gNew += objectCost;
			}

			double hNew = heuristic(ovest, target);
			double fNew = gNew + hNew;

			// if is destination
			if (ovest == target)
			{
				struct node west;
				west.posX = q.posX - 1;
				west.posY = q.posY;
				west.g = gNew;
				west.h = hNew;
				west.f = fNew;
				west.parentX = q.posX;
				west.parentY = q.posY;

				closedList.push_back(q);
				closedList.push_back(west);
				destination = true;
			}
			else
			{
				bool found = false;
				bool minus = false;

				// looking for this node in closedList
				for (std::vector<node>::iterator i = closedList.begin(); i<closedList.end(); i++)
				{
					if (i->posX == q.posX - 1 && i->posY == q.posY)
					{
						found = true;
						break;
					}
				}

				if (!found)
				{
					// looking for this node in openList
					for (std::vector<node>::iterator i = openList.begin(); i<openList.end(); i++)
					{
						if (i->posX == q.posX - 1 && i->posY == q.posY)
						{
							found = true;
							if (i->f > fNew)
								minus = true;
							break;
						}
					}

					if (!found || (found && minus))
					{
						struct node west;
						west.posX = q.posX - 1;
						west.posY = q.posY;
						west.g = gNew;
						west.h = hNew;
						west.f = fNew;
						west.parentX = q.posX;
						west.parentY = q.posY;

						openList.push_back(west);
					}
				}

			}

		}

		//----------- 5th Successor North-East (x+1, y-1) ------------

		coord nordEst(q.posX + 1, q.posY - 1);

		if (!destination && !pavimento.at(posizione(nordEst)).isMuro() && !pavimento.at(posizione(nordEst)).hasTrap() && pavimento.at(posizione(nord)).getEntita() != nullptr)
		{

			double gNew = q.g + diagonalCost;
			if (pavimento.at(posizione(nordEst)).getOggetti().size() != 0)
			{
				gNew += objectCost;
			}

			double hNew = heuristic(nordEst, target);
			double fNew = gNew + hNew;

			// if is destination
			if (nordEst == target)
			{
				struct node northEast;
				northEast.posX = q.posX + 1;
				northEast.posY = q.posY - 1;
				northEast.g = gNew;
				northEast.h = hNew;
				northEast.f = fNew;
				northEast.parentX = q.posX;
				northEast.parentY = q.posY;

				closedList.push_back(q);
				closedList.push_back(northEast);
				destination = true;
			}
			else
			{
				bool found = false;
				bool minus = false;

				// looking for this node in closedList
				for (std::vector<node>::iterator i = closedList.begin(); i<closedList.end(); i++)
				{
					if (i->posX == q.posX + 1 && i->posY == q.posY - 1)
					{
						found = true;
						break;
					}
				}

				if (!found)
				{
					// looking for this node in openList
					for (std::vector<node>::iterator i = openList.begin(); i<openList.end(); i++)
					{
						if (i->posX == q.posX + 1 && i->posY == q.posY - 1)
						{
							found = true;
							if (i->f > fNew)
								minus = true;
							break;
						}
					}

					if (!found || (found && minus))
					{
						struct node northEast;
						northEast.posX = q.posX + 1;
						northEast.posY = q.posY - 1;
						northEast.g = gNew;
						northEast.h = hNew;
						northEast.f = fNew;
						northEast.parentX = q.posX;
						northEast.parentY = q.posY;

						openList.push_back(northEast);
					}
				}

			}

		}

		//----------- 6th Successor North-West (x-1, y-1) ------------

		coord nordOvest(q.posX - 1, q.posY - 1);

		if (!destination && !pavimento.at(posizione(nordOvest)).isMuro() && !pavimento.at(posizione(nordOvest)).hasTrap() && pavimento.at(posizione(nord)).getEntita() != nullptr)
		{

			double gNew = q.g + diagonalCost;
			if (pavimento.at(posizione(nordOvest)).getOggetti().size() != 0)
			{
				gNew += objectCost;
			}

			double hNew = heuristic(nordOvest, target);
			double fNew = gNew + hNew;

			// if is destination
			if (nordOvest == target)
			{
				struct node northWest;
				northWest.posX = q.posX - 1;
				northWest.posY = q.posY - 1;
				northWest.g = gNew;
				northWest.h = hNew;
				northWest.f = fNew;
				northWest.parentX = q.posX;
				northWest.parentY = q.posY;

				closedList.push_back(q);
				closedList.push_back(northWest);
				destination = true;
			}
			else
			{
				bool found = false;
				bool minus = false;

				// looking for this node in closedList
				for (std::vector<node>::iterator i = closedList.begin(); i<closedList.end(); i++)
				{
					if (i->posX == q.posX - 1 && i->posY == q.posY - 1)
					{
						found = true;
						break;
					}
				}

				if (!found)
				{
					// looking for this node in openList
					for (std::vector<node>::iterator i = openList.begin(); i<openList.end(); i++)
					{
						if (i->posX == q.posX - 1 && i->posY == q.posY - 1)
						{
							found = true;
							if (i->f > fNew)
								minus = true;
							break;
						}
					}

					if (!found || (found && minus))
					{
						struct node northWest;
						northWest.posX = q.posX - 1;
						northWest.posY = q.posY - 1;
						northWest.g = gNew;
						northWest.h = hNew;
						northWest.f = fNew;
						northWest.parentX = q.posX;
						northWest.parentY = q.posY;

						openList.push_back(northWest);
					}
				}

			}

		}

		//----------- 7th Successor South-East (x+1, y+1) ------------

		coord sudEst(q.posX + 1, q.posY + 1);

		if (!destination && !pavimento.at(posizione(sudEst)).isMuro() && !pavimento.at(posizione(sudEst)).hasTrap() && pavimento.at(posizione(nord)).getEntita() != nullptr)
		{

			double gNew = q.g + diagonalCost;
			if (pavimento.at(posizione(sudEst)).getOggetti().size() != 0)
			{
				gNew += objectCost;
			}

			double hNew = heuristic(sudEst, target);
			double fNew = gNew + hNew;

			// if is destination
			if (sudEst == target)
			{
				struct node southEast;
				southEast.posX = q.posX + 1;
				southEast.posY = q.posY + 1;
				southEast.g = gNew;
				southEast.h = hNew;
				southEast.f = fNew;
				southEast.parentX = q.posX;
				southEast.parentY = q.posY;

				closedList.push_back(q);
				closedList.push_back(southEast);
				destination = true;
			}
			else
			{
				bool found = false;
				bool minus = false;

				// looking for this node in closedList
				for (std::vector<node>::iterator i = closedList.begin(); i<closedList.end(); i++)
				{
					if (i->posX == q.posX + 1 && i->posY == q.posY + 1)
					{
						found = true;
						break;
					}
				}

				if (!found)
				{
					// looking for this node in openList
					for (std::vector<node>::iterator i = openList.begin(); i<openList.end(); i++)
					{
						if (i->posX == q.posX + 1 && i->posY == q.posY + 1)
						{
							found = true;
							if (i->f > fNew)
								minus = true;
							break;
						}
					}

					if (!found || (found && minus))
					{
						struct node southEast;
						southEast.posX = q.posX + 1;
						southEast.posY = q.posY + 1;
						southEast.g = gNew;
						southEast.h = hNew;
						southEast.f = fNew;
						southEast.parentX = q.posX;
						southEast.parentY = q.posY;

						openList.push_back(southEast);
					}
				}

			}

		}

		//----------- 8th Successor South-West (x-1, y+1) ------------

		coord sudOvest(q.posX - 1, q.posY + 1);

		if (!destination && !pavimento.at(posizione(sudOvest)).isMuro() && !pavimento.at(posizione(sudOvest)).hasTrap() && pavimento.at(posizione(nord)).getEntita() != nullptr)
		{

			double gNew = q.g + diagonalCost;
			if (pavimento.at(posizione(sudOvest)).getOggetti().size() != 0)
			{
				gNew += objectCost;
			}

			double hNew = heuristic(sudOvest, target);
			double fNew = gNew + hNew;

			// if is destination
			if (sudOvest == target)
			{
				struct node southWest;
				southWest.posX = q.posX - 1;
				southWest.posY = q.posY + 1;
				southWest.g = gNew;
				southWest.h = hNew;
				southWest.f = fNew;
				southWest.parentX = q.posX;
				southWest.parentY = q.posY;

				closedList.push_back(q);
				closedList.push_back(southWest);
				destination = true;
			}
			else
			{
				bool found = false;
				bool minus = false;

				// looking for this node in closedList
				for (std::vector<node>::iterator i = closedList.begin(); i<closedList.end(); i++)
				{
					if (i->posX == q.posX - 1 && i->posY == q.posY + 1)
					{
						found = true;
						break;
					}
				}

				if (!found)
				{
					// looking for this node in openList
					for (std::vector<node>::iterator i = openList.begin(); i<openList.end(); i++)
					{
						if (i->posX == q.posX - 1 && i->posY == q.posY + 1)
						{
							found = true;
							if (i->f > fNew)
								minus = true;
							break;
						}
					}

					if (!found || (found && minus))
					{
						struct node southWest;
						southWest.posX = q.posX - 1;
						southWest.posY = q.posY + 1;
						southWest.g = gNew;
						southWest.h = hNew;
						southWest.f = fNew;
						southWest.parentX = q.posX;
						southWest.parentY = q.posY;

						openList.push_back(southWest);
					}
				}

			}


		}

		if (!destination)
		{
			// Push q on the closedList
			closedList.push_back(q);
		}

	}

	for (std::vector<node>::iterator i = closedList.begin(); i < closedList.end(); i++)
	{
		std::cout << "( " << i->posX << ", " << i->posY << " ) -> " << i->f << std::endl;
	}

	/////////////////////////////
	/* End of A* Algorithm */
}


void Piano::StampaFileChar()
{
	std::ofstream file("mappa.map");
	for (int i = 0; i < lunghezza*larghezza; i++)
	{
		auto casella = pavimento.at(i);
		auto entity = casella.getEntita();
		//Per ora l'ordine va bene così, ma non è detto che in un muro non ci possano essere nemici (tipo fantasmi)
		//FIXME dev'essere come l'altra stampa
		if (dynamic_cast<Protagonista*>((&entity)->get()) != nullptr) //se entity è NULL il dynamic cast risponde NULL
		{
			file << '@';
		}
		else if (casella.isMuro()) //se entity è NULL il dynamic cast risponde NULL
		{
			file << '#';
		}
		else if (dynamic_cast<Attore*>((&entity)->get()) != nullptr) //Same
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
		std::list<std::shared_ptr<Oggetto>> inventario{ std::shared_ptr<Oggetto>(new Oggetto(0.5, "Sfera di metallo", "Direi piuttosto che si tratta di un oggetto a forma d'uovo", 2)) };
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
		appoggio = std::make_shared<Attore>("Goblin puzzone", inventario, scarso, equipaggiamento, 1.1);
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
		oggetto = std::make_shared<Oggetto>(1, "Sfera di metallo", "L'inutilita' fatta lucida.", 0);
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
		oggetto = std::make_shared<Oggetto>(0.25, "Fermaporte", "Non particolarmente utile qui", 4);
		break;
	}
	case 4: {
		oggetto = std::make_shared<Arma>(3, "Cannone laser automatico", "No kill like overkill", 4500, Danno({ 0,0,0,0.5,0.5 }, 600));
		break;
	}
	}
	return oggetto;
}

