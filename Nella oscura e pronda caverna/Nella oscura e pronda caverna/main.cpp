#include <iostream>
#include <ctime>
#include "Oggetto.h"
#include "Entita.h"
#include "Piano.h"
int main() 
{
	//Entita player1("Pippo",Attributi()); // Il costruttore vuoto di Attributi non deve esistere
	//std::cout << "Giocatore: " << player1.getNome() << std::endl;

	Oggetto idolo(15., "Hatkanda", "L'oggetto di un film generico", 400); 
	std::cout << idolo.getDescrizione() << std::endl << idolo.getNome() << std::endl << idolo.getPeso() << std::endl <<
		idolo.getValore();
	char a = 0;
	std::vector<Oggetto> tabellaLoot; //VUOTA
	std::vector<Entita> tabellaEntita; //VUOTA
	Protagonista Saitama("Saitama",tabellaLoot,Attributi(),tabellaLoot,1,0.,0); //Sto usando tabella loot giusto perchè è vuota
	Piano primoLivello(50,50,1,tabellaLoot,tabellaEntita);
	int stanzeCostruite = 0;
	srand(time(NULL));
	for (int i = 0; i < 15; i++)
	{
		int a[4];
		for (int j = 0; j < 4; j++)
		{
			if(j<2)
				a[j] = (int) rand()%50;
			else
				a[j] = (int) rand()%3+8;
		}
		if (primoLivello.creaStanzaRettangolare(a[0], a[1], a[2], a[3]))
			stanzeCostruite++;
	}
	std::cout <<std::endl << stanzeCostruite << std::endl;
	//Finirò in un test!!!
	while (!primoLivello.at((int)rand() % 50, (int)rand() % 50).setEntita(&Saitama)){}

	primoLivello.StampaChar();
	primoLivello.StampaFileChar();
	std::cout << std::endl;
	std::cin >> a;
  //Questo main dovrà finire in un test.
}