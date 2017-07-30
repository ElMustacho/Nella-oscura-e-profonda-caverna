#include <fstream>
#include <iostream>
#include <cmath>
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

Piano::Piano(int larghezza, int lunghezza, std::vector<Oggetto> lootPossibile, std::vector<Entita> entitàPossibili)
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
*/

bool Piano::creaStanzaRettangolare(int posX, int posY, int dimX, int dimY) {
	if (posX + dimX  > lunghezza || posY + dimY > larghezza)
		return false; //Stanza prodotta fuori dal piano
	
	for (int i = posX; i < dimX + posX; i++) {
		for (int j = posY; j < dimY + posY; j++)
			if (!pavimento.at(posizione(i,j)).isMuro()) {
				return false; //Spazio per stanza non trovato
			}
	}
	for (int i = posX; i < dimX + posX; i++) {
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

void Piano::StampaChar() { 
	std::string mappa="";
	for (int i = 0; i < pavimento.size(); i++)
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
//TODO x e y sono invertiti
int Piano::muoviEntita(int posX, int posY, int targetX, int targetY) //I primi due sono quelli da dove parto, gli altri dove arrivo
{
	if (pavimento.at(posizione(posX, posY)).getEntita() == NULL) {
		return -1;//Qui non c'è nessuno
	}
	if (posX == targetX&&posY == targetY) //Questo significa non spostarsi per davvero
		return -2;
	if (!(targetX>-1 && targetX < larghezza && targetY>-1 && targetY < lunghezza))
		return -3; //Posizione non valida per almeno una delle coordinate
	int distanza, metodo;
	pavimento.at(posizione(posX, posY)).getEntita()->muovi(distanza,metodo);
	if (distanza == 0)
		return -4; //Ho provato a muovermi ma sono immobile

	//TODO Dijkstra per determinare la direzione da percorrere (qualora sia necessario usarlo).
	//Qui sotto il sistema di spostamento è stupido, ma potrebbe funzionare per gestire entità prive di intelligenza
	//tipo qualche golem, melma, zombie o goblin ubriaco fradicio. In pratica non verifico la validità finale del percorso,
	//ma solo quella della casella in cui mi voglio spostare, una per volta.
	//P.S. questo sistema funziona bene anche quando c'è solo una casella da percorrere.
	//FIXME da qui assumo che il movimento sia in linea retta
	while (distanza != 0 && !(posX == targetX&&posY == targetY)) { //Esco quando ho terminato i movimenti o quando sono arrivato.
		int moveX=0, moveY=0;
		if (posX < targetX)
			moveX = 1;
		else if (posX > targetX)
			moveX = -1;
		else {}
		if (posY < targetY)
			moveY = 1;
		else if (posY > targetY)
			moveY = -1;
		else {}
		
		if (pavimento.at(posizione(posX + moveX, posY + moveY)).isMuro()) 
		//Qui l'unico controllo presente è che la casella non sia un muro e che nella casella non ci sia nessuno.
		{  
			return 1;
		}
		else if (pavimento.at(posizione(posX + moveX, posY + moveY)).getEntita() != NULL) //Qui c'è qualcun'altro
		{
			return 2;
		}
		else { //Date le premesse, spostarsi è sicuro e valido
			Entita * temp = pavimento.at(posizione(posX, posY)).getEntita();
			pavimento.at(posizione(posX, posY)).setEntita(NULL);
			pavimento.at(posizione(posX + moveX, posY + moveY)).setEntita(temp);
			posX += moveX;
			posY += moveY;
			pavimento.at(posizione(posX, posY)).doEvento();
			distanza--;
		}
	}
	if (distanza == 0 && (posX == targetX&&posY == targetY))
		return 0; //sono arrivato precisamente a destinazione
	else if (distanza != 0 && (posX == targetX&&posY == targetY))
		return 3; //sono arrivato a destinazione ma avevo movimento avanzato
	else return 4; //non sono arrivato a destinazione perché ho finito il movimento
}

void Piano::StampaFileChar() {
	std::ofstream file ("mappa.map");
	for (int i = 0; i < lunghezza*larghezza; i++)
	{
		auto casella = pavimento.at(i);
		auto entity = casella.getEntita();
		//Per ora l'ordine va bene così, ma non è detto che in un muro non ci possano essere nemici (tipo fantasmi)
		if (dynamic_cast<Protagonista*>(entity) != NULL) //se entity è NULL il dynamic cast risponde NULL
			file << '@';
		else if (casella.isMuro()) //se entity è NULL il dynamic cast risponde NULL
			file << '#';
		else if (dynamic_cast<Attore*>(entity) != NULL) //Same
			file << '*';
		else
			file << '.';
		if ((i + 1) % lunghezza == 0)
			file << std::endl;
	}
	file.close();
}