#include <fstream>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <typeinfo>
#include <deque>
#include <time.h>

#include "pianoCavernaIsolaGrafica.h"
#include "SFML\Graphics.hpp"
#include "Piano.h"
#include "TexTBox.h"


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

int Piano::scontro(cood posizioneVittima, cood posizioneAttaccante, TextBox& messages)
{
	if (pavimento.at(posizione(posizioneAttaccante)).getEntita() == nullptr)
		return -1; //nessun attaccante
	auto danno = pavimento.at(posizione(posizioneAttaccante)).getEntita()->attacca();
	if (danno.getAmmontare() < 0)
		return -2; //nessun danno
	else
		return scontro(posizioneVittima, danno, messages );//
}
int Piano::scontro(cood posizioneVittima, Danno dannoInflitto, TextBox& messages)
{
	if (pavimento.at(posizione(posizioneVittima)).getEntita().get() == nullptr)
		return -3; //nessun bersaglio
	else {
		auto morteAvvenuta = pavimento.at(posizione(posizioneVittima)).getEntita()->subisciDanno(dannoInflitto, messages);
		if (morteAvvenuta) {
			//TODOFAR lascia equipaggiamento per terra.
			auto vPosizioni = getVectorPosizioni();
			auto it = std::find(vPosizioni.begin(), vPosizioni.end(), posizioneVittima);
			//HACK devo chiamare removeEntita
			entitaPresenti.erase(entitaPresenti.begin() + std::distance(vPosizioni.begin(), it));
			pavimento.at(posizione(posizioneVittima)).drop();
			pavimento.at(posizione(posizioneVittima)).setEntita(nullptr);
			return 1;
		}
	}
	return 0; 
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

bool Piano::placeEntita(std::shared_ptr<Entita> placeMe, cood coord) 
{
	if (pavimento.at(posizione(coord)).isMuro())
		return false;
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

//CHECK x e y sono invertiti
int Piano::muoviEntita(int posX, int posY, int targetX, int targetY) //I primi due sono quelli da dove parto, gli altri dove arrivo
{
	coord pos(posX, posY);
	coord target(targetX, targetY);
	//FIXME return -2 non può essere mai raggiunto perché tale caso rientra nel return -1
	if ( pavimento.at(posizione(pos)).getEntita() == nullptr )
	{
		return -1; //Qui non c'è nessuno
	}
	if ( pos == target ) //Questo significa non spostarsi per davvero
	{
		return -2;
	}
	if ( !isCoodLegal(target) )
	{
		return -3; //Posizione non valida per almeno una delle coordinate
	}

	int distanza, metodo;
	pavimento.at(posizione(pos)).getEntita()->muovi(distanza, metodo);

	if ( distanza == 0 )
	{
		return -4; //Ho provato a muovermi ma sono immobile
	}

	// CHECK A* (Dijkstra + heuristic) per determinare la direzione da percorrere (qualora sia necessario usarlo).
	//Qui sotto il sistema di spostamento è stupido, ma potrebbe funzionare per gestire entità prive di intelligenza
	//tipo qualche golem, melma, zombie o goblin ubriaco fradicio. In pratica non verifico la validità finale del percorso,
	//ma solo quella della casella in cui mi voglio spostare, una per volta.
	//P.S. questo sistema funziona bene anche quando c'è solo una casella da percorrere.

	if ( typeid(*(pavimento.at(posizione(pos)).getEntita())) != typeid(Protagonista) )
	{
		auto ret = aStar(pos, target, distanza, metodo);

		while ( ret == 5 )
		{
			//CHECK Change target/behavior
			srand(time(NULL));
			
			auto behave = rand() % 2 + 1;
			coord newCoord(rand() % lunghezza - 1, rand() % larghezza - 1);

			switch (behave)
			{
				case 1: // Patrol
					while ( !isCoodLegal(newCoord) && pavimento.at(posizione(newCoord)).getEntita() != nullptr && pavimento.at(posizione(newCoord)).hasTrap() && pavimento.at(posizione(newCoord)).isMuro() )
					{
						newCoord.first = rand() % lunghezza - 1;
						newCoord.second = rand() % larghezza - 1;
					}
					break;
				case 2: // Go and wait near the stairs
					for ( auto i = 0; i != pavimento.size(); i++ )
					{
						if ( pavimento.at(i).getEvento() == 1 )
						{
							newCoord = fromPosizioneToInt(i);
						}
					}
					break;
				case 3: // Freeze (never going to happen - see the rand value...)
					newCoord = pos;
					break;
				default:
					std::cout << "Something wrong, now I long for yesterday..." << std::endl;
			}

			ret = aStar(pos, newCoord, distanza, metodo);
		}
		return ret;
	}
	else
	{
		//CHECK da qui assumo che il movimento sia in linea retta
		while ( distanza != 0 && !(pos == target) ) //Esco quando ho terminato i movimenti o quando sono arrivato.
		{
			int moveX = 0, moveY = 0;

			if ( pos.first < target.first )
			{
				moveX = 1;
			}
			else if ( pos.first > target.first )
			{
				moveX = -1;
			}
			else {}

			if ( pos.second < target.second )
			{
				moveY = 1;
			}
			else if ( pos.second > target.second )
			{
				moveY = -1;
			}
			else //FIXME Not necessary?
			{
			}

			coord updatePos(pos.first + moveX, pos.second + moveY);

			//Qui l'unico controllo presente è che la casella non sia un muro e che nella casella non ci sia nessuno.
			if ( pavimento.at(posizione(updatePos)).isMuro() ) //Qui c'è un muro
			{
				std::cout << "Sbam!" << std::endl;
				return 1;
			}
			else if ( pavimento.at(posizione(updatePos)).getEntita() != nullptr ) //Qui c'è qualcun'altro
			{
				return 2;
			}
			else //Date le premesse, spostarsi è sicuro e valido
			{
				std::shared_ptr<Entita> temp = pavimento.at(posizione(pos)).getEntita();
				pavimento.at(posizione(pos)).setEntita(nullptr);
				pavimento.at(posizione(pos.first + moveX, pos.second + moveY)).setEntita(temp);
				cood coordinatePrima(pos.first, pos.second);
				pos.first += moveX;
				pos.second += moveY;
				cood coordinateDopo(pos.first, pos.second);
				auto vPosizioni = getVectorPosizioni();
				auto it = std::find(vPosizioni.begin(), vPosizioni.end(), coordinatePrima);
				if ( it != vPosizioni.end() ) 
				{
					auto distanza = std::distance(vPosizioni.begin(), it);
					entitaPresenti[distanza].second = coordinateDopo;
				}
				if ( pavimento.at(posizione(pos)).getEvento() != 1 )
				{
					pavimento.at(posizione(pos)).doEvento();
				}
				distanza--;
				pavimento.at(posizione(coordinateDopo)).doEvento();
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


}

//TODOFAR il carattere stampato deve essere restituito dalla casella tramite una sua funzione


int Piano::muoviEntita(coord pos, coord target) //I primi due sono quelli da dove parto, gli altri dove arrivo
{
	return muoviEntita(pos.first, pos.second, target.first, target.second);
}


void Piano::checkSuccessor(coord check, coord target, std::string direct, bool &destination, node &q, std::vector<node> &openList, std::vector<node> &closedList)
{
	// Costs
	auto normalCost = 1;
	auto diagonalCost = sqrt(2);
	auto objectCost = 0.5;

	if (!destination && !pavimento.at(posizione(check)).isMuro() && !pavimento.at(posizione(check)).hasTrap() ) // && pavimento.at(posizione(check)).getEntita() == nullptr
	{
		double gNew = q.g;

		if (direct.compare("nord") == 0 || direct.compare("sud") == 0 || direct.compare("est") == 0 || direct.compare("ovest") == 0)
		{
			gNew += normalCost;
		}
		else if (direct.compare("nordEst") == 0 || direct.compare("nordOvest") == 0 || direct.compare("sudEst") == 0 || direct.compare("sudOvest") == 0)
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
			//bool minus = false;

			// looking for this node in closedList
			for (std::vector<node>::iterator i = closedList.begin(); i < closedList.end(); i++)
			{
				if (i->posX == direction.posX && i->posY == direction.posY)
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
						if ( gNew < i->g )
						{
							//minus = true;
							*i = direction; 
						}
						break;
					}
				}

				if (!found)
				{
					openList.push_back(direction);
				}
			}

		}

	}
	else
	{
		if (check == target)
		{

			std::cout << "Non posso raggiungere la destinazione, solo andarci vicino" << std::endl;
			closedList.push_back(q);
			destination = true;
		}
	}
}


int Piano::aStar(coord pos, coord target, int distanza, int metodo)
{

	std::vector<node> openList;
	std::vector<node> closedList;
	std::vector<node> path;

	bool destination = false;
	auto beginHeuristic = heuristic(pos, target);

	struct node startingNode(pos.first, pos.second, pos.first, pos.second, beginHeuristic, 0, beginHeuristic);
	openList.push_back(startingNode);

	while (!openList.empty() && !destination)
	{
		double minF = DBL_MAX;
		std::vector<node>::iterator position;
		struct node q;

		// find the min 'f' node in openList
		for (std::vector<node>::iterator i = openList.begin(); i < openList.end(); i++)
		{
			if (i->f < minF)
			{
				minF = i->f;
				position = i;
			}
		}
		// Save the node and erase it from openList
		q = *position;
		openList.erase(position);

		/* Generates 8 successors (nearby cells) */

		//----------- 1st Successor North (x, y-1) ------------

		coord nord(q.posX, q.posY - 1);
		if (isCoodLegal(nord))
		{
			checkSuccessor(nord, target, "nord", destination, q, openList, closedList);
		}

		//----------- 2nd Successor South (x, y+1) ------------

		coord sud(q.posX, q.posY + 1);
		if (isCoodLegal(sud))
		{
			checkSuccessor(sud, target, "sud", destination, q, openList, closedList);
		}

		//----------- 3rd Successor East (x+1, y) ------------

		coord est(q.posX + 1, q.posY);
		if (isCoodLegal(est))
		{
			checkSuccessor(est, target, "est", destination, q, openList, closedList);
		}

		//----------- 4th Successor West (x-1, y) ------------

		coord ovest(q.posX - 1, q.posY);
		if (isCoodLegal(ovest))
		{
			checkSuccessor(ovest, target, "ovest", destination, q, openList, closedList);
		}

		//----------- 5th Successor North-East (x+1, y-1) ------------

		coord nordEst(q.posX + 1, q.posY - 1);
		if (isCoodLegal(nordEst))
		{
			checkSuccessor(nordEst, target, "nordEst", destination, q, openList, closedList);
		}

		//----------- 6th Successor North-West (x-1, y-1) ------------

		coord nordOvest(q.posX - 1, q.posY - 1);
		if (isCoodLegal(nordOvest))
		{
			checkSuccessor(nordOvest, target, "nordOvest", destination, q, openList, closedList);
		}

		//----------- 7th Successor South-East (x+1, y+1) ------------

		coord sudEst(q.posX + 1, q.posY + 1);
		if (isCoodLegal(sudEst))
		{
			checkSuccessor(sudEst, target, "sudEst", destination, q, openList, closedList);
		}

		//----------- 8th Successor South-West (x-1, y+1) ------------

		coord sudOvest(q.posX - 1, q.posY + 1);
		if (isCoodLegal(sudOvest))
		{
			checkSuccessor(sudOvest, target, "sudOvest", destination, q, openList, closedList);
		}

		if (!destination)
		{
			// Push q on the closedList
			closedList.push_back(q); //LOOKATME potrei aggiungerlo comunque prima dei successori ed evitare il controllo
		}

	}

	if (!destination)
	{
		return 5; // Non trovo una via per arrivare a destinazione
	}

	// BEGIN Path creation
	path = closedList;
	std::reverse(path.begin(), path.end());

	for (std::vector<node>::iterator i = path.begin(); i < path.end()-1; )
	{
		if ( i->parentX != (i+1)->posX || i->parentY != (i+1)->posY )
		{
			path.erase(i + 1);
			//i--;
		}
		else
		{
			i++;
		}
	}

	std::reverse(path.begin(), path.end());
	// END Path creation

	for (std::vector<node>::iterator i = path.begin(); i+1 != path.end() && distanza > 0; i++)
	{
		//std::cout << "( " << i->posX << ", " << i->posY << " ) -> " << i->f << std::endl;
		cood coordinatePrima(pos.first, pos.second);
		//CHECK muovi enita
		pos.first = i->posX;
		pos.second = i->posY;
		coord next((i + 1)->posX, (i + 1)->posY);

		if (pavimento.at(posizione(next)).getEntita() != nullptr) // Qui c'è qualcun altro
		{
			std::cout << "Qualcuno osa sbarrarmi la strada!" << std::endl;
			//TODO Combatto per liberar la via?
			return 2;
		}
		std::shared_ptr<Entita> temp = pavimento.at(posizione(pos)).getEntita();
		pavimento.at(posizione(pos)).setEntita(nullptr);
		pavimento.at(posizione(next)).setEntita(temp);

		auto vPosizioni = getVectorPosizioni();
		auto it = std::find(vPosizioni.begin(), vPosizioni.end(), coordinatePrima);
		if (it != vPosizioni.end())
		{
			auto distanza = std::distance(vPosizioni.begin(), it);
			entitaPresenti[distanza].second = next;
		}

		//StampaChar();
		pavimento.at(posizione(next)).doEvento();
		distanza--;
		
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

int Piano::playPiano(sf::RenderWindow& window, TextBox& messages)
{
	int spwTurni = 0;
	int totTurni = 0;
	bool a;
	char input = '1';
	std::cout << "Bloat text? y/n: ";
	while (input != 'y'&&input != 'n')
		std::cin >> input;
	if (input == 'y')
		a = true;
	else
		a = false;
	std::deque<std::shared_ptr<Entita>> turni;
	for each (auto it in entitaPresenti)
	{
		turni.push_back(it.first);
	}
	while (!turni.empty()) {
		if (spwTurni > 50 + rand() % 100) { //dopo ogni 50 turni arriva un ulteriore goblin puzzone, di sicuro dopo 150
			auto caselleOk=floodFill(getPositionOfPlayer());
			cood casellaSpawn;
			do //FIXME se non c'è nessuna casella libera sballo
				casellaSpawn = caselleOk[rand() % caselleOk.size()];
			while(!placeEntita(entityFactory(1), casellaSpawn));
			auto smt = pavimento.at(posizione(casellaSpawn)).getEntita();
			turni.push_back(smt);
			auto nomeDaDare = smt->getNome();
			nomeDaDare.append(" arrivato al turno "+std::to_string(totTurni));
			smt->setNome(nomeDaDare);
			spwTurni = 0;
		}
		auto attivo = turni.front();
		turni.pop_front();
		if (pavimento.at(posizione(getPositionOfEntity(attivo))).getEntita() == nullptr) { //
			
			continue;
		}
		std::cout << "Adesso sta a " << attivo->getNome() << std::endl;
		auto posizioneAttivo = getPositionOfEntity(attivo);
		if (getPositionOfPlayer() != posizioneAttivo) {
			//HACK qui si muove e basta, ma poi dovrà decidere l'intelligenza artificiale dell'entità
			auto resultMovement=muoviEntita(posizioneAttivo, getPositionOfPlayer());
		}
		else {
			auto resultPlayer = playerAct(a, window, messages);
			while(resultPlayer<0)
			{ 
				resultPlayer = playerAct(a, window, messages);
			}
			if (resultPlayer == 2) {
				turni.clear();
				return 0;
			}
			spwTurni++;
			totTurni++;
		}
		turni.push_back(attivo);
	}
	
}
//LOOKATME questa è la versione del terminale, quella grafica dovrà lavorare in altri modi.
//return -1 significa che non è passato un turno, per esempio guardando il proprio inventario o per terra
int Piano::playerAct(bool a, sf::RenderWindow& window, TextBox& messages)
{
		StampaChar();
		if (a)
		{
			std::cout << std::endl << "Usa il tastierino numerico per muoverti, 5 per uscire, 0 per guardare a terra,p per raccogliere cio' che e' a terra, e per equipaggiare il primo oggetto nell'inventario nel posto dell'arma, k per suicidarsi, i per descrivere il proprio inventario: ";
			messages.text.setString(messages.text.getString() + "\nUsa il tastierino numerico per muoverti, 5 per uscire, 0 per guardare a terra,p per raccogliere cio' che e' a terra, e per equipaggiare il primo oggetto nell'inventario nel posto dell'arma, k per suicidarsi, i per descrivere il proprio inventario: ");
		}
		char azione;
		std::cin >> azione;
		std::cout << std::endl;
		system("CLS");
		messages.text.setString("");
		auto playerPos = getPositionOfPlayer();
		auto toPosizione = playerPos;
		int result;

		switch (azione){
		case '1':
			toPosizione.first--;
			toPosizione.second++;
			break;
		case '2':
			toPosizione.second++;
			break;
		case '3':
			toPosizione.first++;
			toPosizione.second++;
			break;
		case '4':
			toPosizione.first--;
			break;
		case '6':
			toPosizione.first++;
			break;
		case '7':
			toPosizione.first--;
			toPosizione.second--;
			break;
		case '8':
			toPosizione.second--;
			break;
		case '9':
			toPosizione.first++;
			toPosizione.second--;
			break;
		}
		if (playerPos != toPosizione) //L'azione scelta è un movimento
		{
			result = muoviEntita(playerPos.first, playerPos.second, toPosizione.first, toPosizione.second);
			if (result == 0) {
				if (a)
				{
					std::cout << "Ho provato a muovermi con successo." << std::endl;
					messages.text.setString(messages.text.getString() + "Ho provato a muovermi con successo.\n");
				}
				return 0;
			}
			else if (result==2) {
				if (a)
				{
					std::cout << "Scontro!" << std::endl;
					messages.text.setString( messages.text.getString() + "Scontro!\n");
				}
				scontro(toPosizione, playerPos, messages);
				return 0;
			}
			else {
				if (a)
				{
					std::cout << "Muoversi ha risposto " << result << std::endl;
					messages.text.setString( messages.text.getString() + "Muoversi ha risposto " + std::to_string(result) + "\n");
				}
				return -1;
			}
		}
		else {
			switch (azione) {
				case '5':
					return 2;
				case 's':
					scontro(playerPos, Danno(std::vector<double>{1}, 4000), messages);
					break;
				case 'e':
					pavimento.at(posizione(playerPos)).getEntita()->equip(window, messages);
					break;
				case '0':
					std::cout << pavimento.at(posizione(getPositionOfPlayer())).descriviOggettiTerra();
					return -1;
				case 'p':
					pavimento.at(posizione(getPositionOfPlayer())).pickup();
					break;
				case 'i':
					std::cout << pavimento.at(posizione(playerPos)).getEntita()->describeInventario() << std::endl;
					return -1;
				default:
					if (a)
					{
						std::cout << "Input non valido" << std::endl;
						messages.text.setString(messages.text.getString() + "Input non valido\n");
					}
					return -1;
				}
			}
		return 0;
		
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
//Lasciare vuoto per avere un personaggio principale, oppure mandare 0. Valori non accettati restituiscono un nullptr
std::shared_ptr<Entita> Piano::entityFactory(int codiceID)
{
	std::shared_ptr<Entita> appoggio;
	switch (codiceID) {
	case 0: {
		//TODO qui ovviamente dovrà esserci il modo di caricare un personaggio preesistente o di invocare il creatore di personaggi, per ora lo tratto come un qualunque idiota
		std::vector<std::shared_ptr<Oggetto>> inventario{ std::shared_ptr<Oggetto>(new Oggetto(0.5, "Una pietra", "Terra condensata.", 0)) };
		Attributi nellaMedia(4, 4, 4, 4, 4, 4, 4, 4);
		Equipaggiamento equipaggiamento; //Picche, non hai nulla scemo
		appoggio = std::make_shared<Protagonista>(Protagonista("Medioman", inventario, nellaMedia, equipaggiamento, 1, 0, 0));
		break;
	}
	case 1:
	{// Goblin scrauso, puzzone e nudo
		std::vector<std::shared_ptr<Oggetto>> inventario;
		Attributi scarso(3, 4, 2, 2, 2, 1, 3, 1);
		Equipaggiamento equipaggiamento; //Picche, non hai nulla scemo puzzone
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
