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
	return pavimento.at(y + x * larghezza); 
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
//TODO per ora io prendo solo la struttura del piano, entità e oggetti non verranno considerati
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

double heuristic(int posX, int posY, int targetX, int targetY)
{
	// Octile distance
	auto dx = abs(posX - targetX);
	auto dy = abs(posY - targetY);
	auto D = 1; // Normal cost
	auto D2 = sqrt(2); // Diagonal cost
	return D * (dx + dy) + (D2 - 2 * D) * std::min(dx, dy);
};

//TODO x e y sono invertiti
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

	//TODO A* (Dijkstra + heuristic) per determinare la direzione da percorrere (qualora sia necessario usarlo).
	//Qui sotto il sistema di spostamento è stupido, ma potrebbe funzionare per gestire entità prive di intelligenza
	//tipo qualche golem, melma, zombie o goblin ubriaco fradicio. In pratica non verifico la validità finale del percorso,
	//ma solo quella della casella in cui mi voglio spostare, una per volta.
	//P.S. questo sistema funziona bene anche quando c'è solo una casella da percorrere.

	/* A* Algorithm */
	/////////////////////////////

	struct node
	{
		node(){}
		node(int posX, int posY, int parentX, int parentY, double f, double g, double h) 
		{
			this->posX = posX; 
			this->posY = posY;

			this->parentX = parentX;
			this->parentY = parentY;

			this->f = f;
			this->g = g;
			this->h = h;
		}
		int posX, posY;
		int parentX, parentY;
		double f, g, h;
	};
	

	std::vector<node> openList;
	std::vector<node> closedList;
	bool destination = false;

	struct node startingNode(posX, posY, posX, posY, 0, 0, 0);
	openList.push_back(startingNode);

	while ( !openList.empty() && !destination )
	{
		double min = DBL_MAX;
		std::vector<node>::iterator position;
		struct node q;

		// find the min 'f' node in openList
		for ( std::vector<node>::iterator i = openList.begin(); i < openList.end(); i++ )
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
		
		if ( !pavimento.at(posizione(q.posX, q.posY - 1)).isMuro() && !destination )
		{

			double gNew = q.g + 1;
			double hNew = heuristic(q.posX, q.posY-1, targetX, targetY);
			double fNew = gNew + hNew;

			// if is destination
			if ( q.posX==targetX && q.posY-1==targetY )
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
				for ( std::vector<node>::iterator i = closedList.begin(); i < closedList.end(); i++ )
				{
					if ( i->posX == q.posX && i->posY == q.posY - 1 && i->f < fNew )
					{
						found = true;
						break;
					}
				}

				if (!found)
				{
					// looking for this node in openList
					for ( std::vector<node>::iterator i = openList.begin(); i < openList.end(); i++ )
					{
						if ( i->posX == q.posX && i->posY == q.posY - 1 )
						{
							found = true;
							if (i->f > fNew)
								minus = true;
							break;
						}
					}

					if ( !found || (found && minus) )
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

		if ( !pavimento.at(posizione(q.posX, q.posY + 1)).isMuro() && !destination )
		{

			double gNew = q.g + 1;
			double hNew = heuristic(q.posX, q.posY + 1, targetX, targetY);
			double fNew = gNew + hNew;

			// if is destination
			if (q.posX == targetX && q.posY + 1 == targetY)
			{
				struct node south;
				south.posX = q.posX;
				south.posY = q.posY + 1;
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

		if ( !pavimento.at(posizione(q.posX + 1, q.posY)).isMuro() && !destination )
		{

			double gNew = q.g + 1;
			double hNew = heuristic(q.posX + 1, q.posY, targetX, targetY);
			double fNew = gNew + hNew;

			// if is destination
			if (q.posX + 1 == targetX && q.posY == targetY)
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

		if ( !pavimento.at(posizione(q.posX - 1, q.posY)).isMuro() && !destination )
		{

			double gNew = q.g + 1;
			double hNew = heuristic(q.posX - 1, q.posY, targetX, targetY);
			double fNew = gNew + hNew;

			// if is destination
			if (q.posX - 1 == targetX && q.posY == targetY)
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

		if ( !pavimento.at(posizione(q.posX + 1, q.posY - 1)).isMuro() && !destination )
		{

			double gNew = q.g + 1;
			double hNew = heuristic(q.posX + 1, q.posY - 1, targetX, targetY);
			double fNew = gNew + hNew;

			// if is destination
			if (q.posX + 1 == targetX && q.posY - 1 == targetY)
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

		if ( !pavimento.at(posizione(q.posX - 1, q.posY - 1)).isMuro() && !destination )
		{

			double gNew = q.g + 1;
			double hNew = heuristic(q.posX - 1, q.posY - 1, targetX, targetY);
			double fNew = gNew + hNew;

			// if is destination
			if (q.posX - 1 == targetX && q.posY - 1 == targetY)
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

		if ( !pavimento.at(posizione(q.posX + 1, q.posY + 1)).isMuro() && !destination )
		{

			double gNew = q.g + 1;
			double hNew = heuristic(q.posX + 1, q.posY + 1, targetX, targetY);
			double fNew = gNew + hNew;

			// if is destination
			if (q.posX + 1 == targetX && q.posY + 1 == targetY)
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

					if ( !found || (found && minus) )
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

		if ( !pavimento.at(posizione(q.posX - 1, q.posY + 1)).isMuro() && !destination )
		{

			double gNew = q.g + 1;
			double hNew = heuristic(q.posX - 1, q.posY + 1, targetX, targetY);
			double fNew = gNew + hNew;

			// if is destination
			if (q.posX - 1 == targetX && q.posY + 1 == targetY)
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
		
		if ( !destination )
		{
			// Push q on the closedList
			closedList.push_back(q);
		}

	}

	for (std::vector<node>::iterator i = closedList.begin(); i < closedList.end(); i++)
	{
		std::cout << "( " << i->posX << ", " << i->posY << " ) -> "<< i->f << std::endl;
	}

	/////////////////////////////
	/* End of A* Algorithm */


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