#include <fstream>
#include <iostream>
#include <cmath>
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
	if (x > larghezza)
		x = larghezza;
	if (y > lunghezza)
		y = lunghezza;
	return x + y*larghezza;
}

int Piano::posizione(coord xy) 
{
	if (xy.first < 0)
		xy.first = 0;
	if (xy.second < 0)
		xy.second = 0;
	if (xy.first > larghezza)
		xy.first = larghezza;
	if (xy.second > lunghezza)
		xy.second = lunghezza;
	return xy.first + xy.second * larghezza;
}

//Stesso funzionamento di Piano::posizione()
Casella & Piano::at(int x, int y) 
{ 
	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	if (x > larghezza)
		x = larghezza;
	if (y > lunghezza)
		y = lunghezza;
	return pavimento.at(y + x * larghezza); // LOOKATME dovrebbe essere x + y * larghezza;
}


bool Piano::popolaPiano()
{
	return false;
}

bool Piano::spargiLoot() 
{
	return false;
}

Piano::Piano() {

}

Piano::Piano(int larghezza, int lunghezza, std::vector<Oggetto> lootPossibile, std::vector<Entita> entitaPossibili)
{
}
/*
// TODO per ora io prendo solo la struttura del piano, entità e oggetti non verranno considerati
//in futuro, se da un piano non trovo il personaggio od ho altri probelmi, l'operazione deve fallire, e il piano deve essere scartato
//Chiedo un persorso file, se riesco ad arrivare in fondo successo sarà true, altrimenti false.
Piano::Piano(std::string posizione, bool &successo)
{
	std::ifstream inputPiano(posizione);
	std::string lineaCaselle;
	lunghezza = 0, larghezza = 0;
	for (int i = 0; std::getline(inputPiano, lineaCaselle); i++)
	{
	case 1:
		if (1==1)//TODO controlli sulla validità del piano.
			auto generato = GeneratoreV1();
		break;
	default:
		auto generato = GeneratoreV1();//questo sarà il generatore di default.
		
		for (unsigned int j = 0; j < lineaCaselle.size(); j++)
		{
			if (lineaCaselle.at(j) == '#')
				pavimento.push_back(Casella(false));
			else if (lineaCaselle.at(j) == '.')
				pavimento.push_back(Casella(true));
			else {
				std::cout << "E' successo un casino.\n";
				successo = false;
			}
		}
		if (i == 0)
			larghezza=lineaCaselle.size();
		lunghezza++;
	}
	pavimento.reserve(lunghezza*larghezza); //LOOKATME questa chiamata è molto importante, e deve essere fatta alla fine di ogni costruttore!
}
bool Piano::GeneratoreV1() 
{
	return false;
}
*/

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



void Piano::StampaChar() 
{ 
	std::string mappa="";
	for (unsigned int i = 0; i < pavimento.size(); i++)

	{
		auto casella = pavimento.at(i);
		auto entity = casella.getEntita();
		if (pavimento.at(i).isMuro())
			mappa.push_back('#');
		else if (dynamic_cast<Protagonista*>(entity) != NULL) 
			mappa.push_back('@');
		else if (dynamic_cast<Attore*>(entity) != NULL) 
			mappa.push_back('*');
		else
			mappa.push_back('.');
		if ((i + 1) % larghezza == 0)
			mappa.push_back('\n');
	}
	std::cout << mappa;
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
	// Version: Octile distance
	auto dx = abs(pos.first - target.first);
	auto dy = abs(pos.second - target.second);

	auto normalCost = 1;
	auto diagonalCost = sqrt(2);

	return normalCost * (dx + dy) + (diagonalCost - 2 * normalCost) * std::min(dx, dy);
}

//TODO x e y sono invertiti
int Piano::muoviEntita(int posX, int posY, int targetX, int targetY) //I primi due sono quelli da dove parto, gli altri dove arrivo
{
	if (pavimento.at(posizione(posX, posY)).getEntita() == NULL) // CHECK Dovrebbe essere nullptr, no?
	{
		return -1; //Qui non c'è nessuno
	}
	if (posX == targetX && posY == targetY) //Questo significa non spostarsi per davvero
	{
		return -2;
	}
	if (!(targetX > -1 && targetX<lunghezza && targetY>-1 && targetY < larghezza))
	{
		return -3; //Posizione non valida per almeno una delle coordinate
	}

	int distanza, metodo;
	pavimento.at(posizione(posX, posY)).getEntita()->muovi(distanza,metodo);

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
			Entita* temp = pavimento.at(posizione(posX, posY)).getEntita();
			pavimento.at(posizione(posX, posY)).setEntita(NULL);
			pavimento.at(posizione(posX + moveX, posY + moveY)).setEntita(temp);
			posX += moveX;
			posY += moveY;
			pavimento.at(posizione(posX, posY)).doEvento();
			distanza--;
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


int Piano::muoviEntita(coord pos, coord target) //I primi due sono quelli da dove parto, gli altri dove arrivo
{
	if (pavimento.at(posizione(pos)).getEntita() == NULL) // CHECK Dovrebbe essere nullptr, no?
	{
		return -1; //Qui non c'è nessuno
	}
	if (pos.first == target.first && pos.second == target.second) //Questo significa non spostarsi per davvero
	{
		return -2;
	}
	if (!(target.first > -1 && target.first < lunghezza && target.second > -1 && target.second < larghezza))
	{
		return -3; //Posizione non valida per almeno una delle coordinate
	}

	int distanza, metodo;
	pavimento.at( posizione(pos) ).getEntita()->muovi(distanza, metodo);

	if (distanza == 0)
	{
		return -4; //Ho provato a muovermi ma sono immobile
	}

	// TODO A* (Dijkstra + heuristic) per determinare la direzione da percorrere (qualora sia necessario usarlo).
	//Qui sotto il sistema di spostamento è stupido, ma potrebbe funzionare per gestire entità prive di intelligenza
	//tipo qualche golem, melma, zombie o goblin ubriaco fradicio. In pratica non verifico la validità finale del percorso,
	//ma solo quella della casella in cui mi voglio spostare, una per volta.
	//P.S. questo sistema funziona bene anche quando c'è solo una casella da percorrere.


	aStar(pos, target);

	//FIXME da qui assumo che il movimento sia in linea retta
	while (distanza != 0 && !(pos.first == target.first && pos.second == target.second)) //Esco quando ho terminato i movimenti o quando sono arrivato.
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
		else {}

		coord updatePos(pos.first + moveX, pos.second + moveY);

		//Qui l'unico controllo presente è che la casella non sia un muro e che nella casella non ci sia nessuno.
		if (pavimento.at(posizione(updatePos)).isMuro()) //Qui c'è un muro
		{
			return 1;
		}
		else if (pavimento.at(posizione(updatePos)).getEntita() != NULL) //Qui c'è qualcun'altro
		{
			return 2;
		}
		else //Date le premesse, spostarsi è sicuro e valido
		{
			Entita* temp = pavimento.at( posizione(pos) ).getEntita();
			pavimento.at(posizione(pos)).setEntita(NULL);
			pavimento.at(posizione(pos.first + moveX, pos.second + moveY)).setEntita(temp);
			pos.first += moveX;
			pos.second += moveY;
			pavimento.at(posizione(pos)).doEvento();
			distanza--;
		}
	}
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

		if (!destination && !pavimento.at(posizione(nord)).isMuro() && !pavimento.at(posizione(nord)).hasTrap() && pavimento.at(posizione(nord)).getEntita() != nullptr )
		{

			double gNew = q.g + normalCost;
			if (pavimento.at(posizione(nord)).getOggetto() != nullptr)
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
		
		if (!destination && !pavimento.at(posizione(sud)).isMuro() && !pavimento.at(posizione(sud)).hasTrap() && pavimento.at(posizione(nord)).getEntita() != nullptr )
		{

			double gNew = q.g + normalCost;
			if (pavimento.at(posizione(sud)).getOggetto() != nullptr)
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

		if (!destination && !pavimento.at(posizione(est)).isMuro() && !pavimento.at(posizione(est)).hasTrap() && pavimento.at(posizione(nord)).getEntita() != nullptr )
		{

			double gNew = q.g + normalCost;
			if (pavimento.at(posizione(est)).getOggetto() != nullptr)
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

		if (!destination && !pavimento.at(posizione(ovest)).isMuro() && !pavimento.at(posizione(ovest)).hasTrap() && pavimento.at(posizione(nord)).getEntita() != nullptr )
		{

			double gNew = q.g + normalCost;
			if (pavimento.at(posizione(ovest)).getOggetto() != nullptr)
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

		if (!destination && !pavimento.at(posizione(nordEst)).isMuro() && !pavimento.at(posizione(nordEst)).hasTrap() && pavimento.at(posizione(nord)).getEntita() != nullptr )
		{
			
			double gNew = q.g + diagonalCost;
			if (pavimento.at(posizione(nordEst)).getOggetto() != nullptr)
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

		if (!destination && !pavimento.at(posizione(nordOvest)).isMuro() && !pavimento.at(posizione(nordOvest)).hasTrap() && pavimento.at(posizione(nord)).getEntita() != nullptr )
		{

			double gNew = q.g + diagonalCost;
			if (pavimento.at(posizione(nordOvest)).getOggetto() != nullptr)
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

		if (!destination && !pavimento.at(posizione(sudEst)).isMuro() && !pavimento.at(posizione(sudEst)).hasTrap() && pavimento.at(posizione(nord)).getEntita() != nullptr )
		{

			double gNew = q.g + diagonalCost;
			if (pavimento.at(posizione(sudEst)).getOggetto() != nullptr)
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

		if (!destination && !pavimento.at(posizione(sudOvest)).isMuro() && !pavimento.at(posizione(sudOvest)).hasTrap() && pavimento.at(posizione(nord)).getEntita() != nullptr )
		{

			double gNew = q.g + diagonalCost;
			if (pavimento.at(posizione(sudOvest)).getOggetto() != nullptr)
			{
				gNew += objectCost;
			}

			double hNew = heuristic(sudOvest, target);
			double fNew = gNew + hNew;

			// if is destination
			if (sudOvest  == target)
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
	std::ofstream file ("mappa.map");
	for (int i = 0; i < lunghezza*larghezza; i++)
	{
		auto casella = pavimento.at(i);
		auto entity = casella.getEntita();
		//Per ora l'ordine va bene così, ma non è detto che in un muro non ci possano essere nemici (tipo fantasmi)
		if (dynamic_cast<Protagonista*>(entity) != NULL) //se entity è NULL il dynamic cast risponde NULL
		{
			file << '@';
		}
		else if (casella.isMuro()) //se entity è NULL il dynamic cast risponde NULL
		{
			file << '#';
		}
		else if (dynamic_cast<Attore*>(entity) != NULL) //Same
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
