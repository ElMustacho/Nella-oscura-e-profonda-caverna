#include "pch.h"

#include"..\Nella oscura e pronda caverna\Piano.h"
#include"..\Nella oscura e pronda caverna\Piano.cpp"
#include "..\Nella oscura e pronda caverna\Casella.h"
#include "..\Nella oscura e pronda caverna\Entita.h"
#include "..\Nella oscura e pronda caverna\Sprite.h"
#include "..\Nella oscura e pronda caverna\Casella.cpp"
#include "..\Nella oscura e pronda caverna\Entita.cpp"
#include "..\Nella oscura e pronda caverna\Sprite.cpp"
#include "..\Nella oscura e pronda caverna\Attributi.h"
#include "..\Nella oscura e pronda caverna\Attributi.cpp"
#include "..\Nella oscura e pronda caverna\Tileset.h"
#include "..\Nella oscura e pronda caverna\Tileset.cpp"
#include "..\Nella oscura e pronda caverna\Protagonista.h"
#include "..\Nella oscura e pronda caverna\Protagonista.cpp"
#include "..\Nella oscura e pronda caverna\Attore.h"
#include "..\Nella oscura e pronda caverna\Attore.cpp"
TEST(TestPiano, CostruzioneStanzaGeneratore1) {
	std::vector<Oggetto> tabellaLoot; //VUOTA
	std::vector<Entita> tabellaEntita; //VUOTA
	Piano livelloTest(10, 8, 1, tabellaLoot, tabellaEntita);
	EXPECT_FALSE(livelloTest.creaStanzaRettangolare(0, 0, 15, 15))<<"La stanza dovrebbe essere troppo grande";
	EXPECT_TRUE(livelloTest.creaStanzaRettangolare(4, 4, 3, 2))<<"La stanza non e' stata correttamente inserita";
	EXPECT_FALSE(livelloTest.creaStanzaRettangolare(3, 3, 4, 4))<<"La stanza non doveva essere inserita perche' sovrapposta";
	
}

TEST(TestPiano, TestCostruzioneGenericaMultiplaGeneratore1) { //Prova 50000 volte a costruire un piano, se uno fallisce non arriva in fondo al test
	srand(time(NULL));
	std::vector<Oggetto> tabellaLoot; //VUOTA
	std::vector<Entita> tabellaEntita; //VUOTA
	Protagonista player("personaggio", tabellaLoot, Attributi(), tabellaLoot, 1, 0., 0);
	std::cout << std::endl << "50000 volte costruire stanze in un piano, tempo stimato 12 secondi" << std::endl;
	for (int k = 0; k < 50000; k++)
	{
		Piano primoLivello(50, 50, 1, tabellaLoot, tabellaEntita);
		int stanzeCostruite = 0;
		
		for (int i = 0; i < 15; i++)
		{
			int a[4];
			for (int j = 0; j < 4; j++)
			{
				if (j<2)
					a[j] = (int)rand() % 50;
				else
					a[j] = (int)rand() % 3 + 8;
			}
			if (primoLivello.creaStanzaRettangolare(a[0], a[1], a[2], a[3]))
				stanzeCostruite++;
		}
		while (!primoLivello.at((int)rand() % 50, (int)rand() % 50).setEntita(&player)) {}

	}
	ASSERT_TRUE(true);
}

TEST(TestPiano, TestMovimentoECollisioni) {
	std::vector<Oggetto> tabellaLoot; //VUOTA
	std::vector<Entita> tabellaEntita; //VUOTA
	Protagonista player("Personaggio", tabellaLoot, Attributi(), tabellaLoot, 1, 0., 0);
	Attore monster("Goblin", tabellaLoot, Attributi(), tabellaLoot,1.);
	Piano livello(15, 15, 1, tabellaLoot, tabellaEntita);
	livello.creaStanzaRettangolare(3, 3, 6, 7);
	ASSERT_FALSE(livello.at(1, 1).setEntita(&monster)) << "Ho inserito un'attore dentro un muro";
	ASSERT_FALSE(livello.at(1, 1).setEntita(&player)) << "Ho inserito personaggio dentro un muro";
	ASSERT_TRUE(livello.at(4, 4).setEntita(&player)) << "Non ho inserito un personaggio dove potrebbe stare";
	ASSERT_TRUE(livello.at(5, 5).setEntita(&monster)) << "Non ho inserito un attore dove potrebbe stare";
	ASSERT_EQ(-1, livello.muoviEntita(6, 6, 7, 4)) << "Ho provato a muovere qualcosa che non c'e'";
	ASSERT_EQ(-2, livello.muoviEntita(5, 5, 5, 5)) << "Ho provato a muovermi da un punto allo stesso punto";
	ASSERT_EQ(-3, livello.muoviEntita(5, 5, 5, 50)) << "L'arrivo era fuori dal piano ma mi sono mosso lo stesso";
	ASSERT_EQ(4, livello.muoviEntita(4, 4, 1, 1)) << "Ho terminato il movimento anche se era troppo lungo";
	ASSERT_EQ(&player, livello.at(3, 3).getEntita()) << "Il movimento precedente mi ha condotto qui ma non c'e' nessuno";
	ASSERT_EQ(1, livello.muoviEntita(3, 3, 2, 2)) << "Mi sono spostato dentro un muro";
	ASSERT_EQ(0, livello.muoviEntita(3, 3, 4, 4)) << "Non mi sono mosso anche se potevo e dovevo";
	ASSERT_EQ(2, livello.muoviEntita(4, 4, 5, 5)) << "Ho tamponato un'altra entita' anche se non potevo";

}