#include <fstream>
#include <iostream>
#include <cmath>
#include "Piano.h"


Piano::~Piano()
{
}

int Piano::posizione(int x, int y)
{ 
	if (y <= larghezza && x <= lunghezza)
	{
		return y + x * lunghezza;
	}
	return ; // CHECK caso deve restituire? Gestito in un altro ramo...
}

bool Piano::popolaPiano()
{
	return false;
}

bool Piano::spargiLoot() 
{
	return false;
}


Piano::Piano(int larghezza, int lunghezza, int sceltaGeneratore, std::vector<Oggetto> lootPossibile, std::vector<Entita> entitàPossibili)
{
	this->lunghezza = lunghezza;
	this->larghezza = larghezza;
	pavimento.reserve(lunghezza*larghezza); //Velocizza l'accesso futuro alla memoria.
	pavimento = std::vector<Casella>(lunghezza*larghezza, Casella()); //Riempio tutto di muri all'inizio
	
	switch (sceltaGeneratore)
	{
	case 1:
		if (1==1)//TODO controlli sulla validità del piano.
			auto generato = GeneratoreV1();
		break;
	default:
		auto generato = GeneratoreV1();//questo sarà il generatore di default.
		
	}
}

bool Piano::GeneratoreV1() 
{
	return false;
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

bool Piano::creaPorte(int posX, int posY, int dimX, int dimY) //Presa una stanza, prova a costruirci intorno delle porte
{
	return true;
}

void Piano::StampaChar() 
{
	for (int i = 0; i < lunghezza*larghezza; i++)
	{
		auto casella = pavimento.at(i);
		auto entity = casella.getEntita();
		if (pavimento.at(i).isMuro())
			std::cout << '#'; 
		else if (dynamic_cast<Protagonista*>(entity) != NULL) 
			std::cout << '@';
		else if (dynamic_cast<Attore*>(entity) != NULL) 
				std::cout << '*';
		else
			std::cout << '.';
		if ((i+1)%lunghezza == 0)
			std::cout << std::endl;
	}
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
}