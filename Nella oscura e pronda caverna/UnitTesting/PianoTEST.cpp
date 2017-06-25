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
TEST(TestPiano, CostruzioneStanzaGeneratore1) {
	std::vector<Oggetto> tabellaLoot; //VUOTA
	std::vector<Entita> tabellaEntita; //VUOTA
	Piano livelloTest(10, 8, 1, tabellaLoot, tabellaEntita);
	EXPECT_FALSE(livelloTest.creaStanzaRettangolare(0, 0, 15, 15))<<"Stanza troppo grande";
	EXPECT_TRUE(livelloTest.creaStanzaRettangolare(4, 4, 3, 2))<<"Stanza correttamente inserita";
	EXPECT_FALSE(livelloTest.creaStanzaRettangolare(3, 3, 4, 4))<<"Stanza non inserita perche' sovrapposta";
	
}

TEST(TestPiano, TestCostruzioneGenericaMultiplaGeneratore1) { //Prova 50000 volte a costruire un piano, se uno fallisce non arriva in fondo al test
	srand(time(NULL));
	std::vector<Oggetto> tabellaLoot; //VUOTA
	std::vector<Entita> tabellaEntita; //VUOTA
	Protagonista Saitama("Saitama", tabellaLoot, Attributi(), tabellaLoot, 1, 0., 0);

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
		while (!primoLivello.at((int)rand() % 50, (int)rand() % 50).setEntita(&Saitama)) {}

	}
	ASSERT_TRUE(true);
}