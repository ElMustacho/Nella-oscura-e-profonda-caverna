
#include "stdafx.h"
TEST(TestPiano, CostruzioneStanzaGeneratore1) {
	std::list<std::shared_ptr<Oggetto>> tabellaLoot; //VUOTA
	std::vector<std::shared_ptr<Oggetto>> Equipaggiamento;
	std::vector<std::shared_ptr<Entita>> tabellaEntita; //VUOTA
	Piano livelloTest(10, 8, Equipaggiamento, tabellaEntita);
	EXPECT_FALSE(livelloTest.creaStanzaRettangolare(0, 0, 15, 15)) << "La stanza dovrebbe essere troppo grande";
	EXPECT_TRUE(livelloTest.creaStanzaRettangolare(4, 4, 3, 2)) << "La stanza non e' stata correttamente inserita";
	EXPECT_FALSE(livelloTest.creaStanzaRettangolare(3, 3, 4, 4)) << "La stanza non doveva essere inserita perche' sovrapposta";

}

TEST(TestPiano, TestCostruzioneGenericaMultiplaGeneratore1) { //Prova tante volte a costruire un piano, se uno fallisce non arriva in fondo al test
	srand((unsigned int)time(nullptr));
	std::list<std::shared_ptr<Oggetto>> tabellaLoot; //VUOTA
	std::vector<std::shared_ptr<Oggetto>> inventario;
	std::vector<std::shared_ptr<Entita>> tabellaEntita; //VUOTA
	Protagonista player("Personaggio", inventario, Attributi(), Equipaggiamento(), 4, 15, 400);
	//Protagonista player("Personaggio", Equipaggiamento(), Attributi(), Equipaggiamento(), 1, 5., 40);
	for (int k = 0; k < 200; k++)
	{
		Piano primoLivello(50, 50, inventario, tabellaEntita);
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
		while (!primoLivello.at((int)rand() % 50, (int)rand() % 50).setEntita(std::make_shared<Protagonista>(player))) {}
		if (k % 50 == 0)
			std::cout << "Piano numero " << k << std::endl;
	}
	ASSERT_TRUE(true);
}

TEST(TestPiano, TestMovimentoECollisioni) {
	std::list<std::shared_ptr<Oggetto>> tabellaLoot; //VUOTA
	std::vector<std::shared_ptr<Oggetto>> inventario;
	std::vector<std::shared_ptr<Entita>> tabellaEntita; //VUOTA
	Attributi normale(4, 4, 4, 4, 4, 4, 4, 4);
	Protagonista player("Personaggio", inventario, normale, Equipaggiamento(), 4, 15, 400);
	
	Attore monster("Goblin", inventario, normale, Equipaggiamento(), 1.);
	Piano livello(15, 15, inventario, tabellaEntita);
	livello.creaStanzaRettangolare(3, 3, 6, 7);
	ASSERT_FALSE(livello.at(1, 1).setEntita(std::make_shared<Attore>(monster))) << "Ho inserito un'attore dentro un muro";
	ASSERT_FALSE(livello.at(1, 1).setEntita(std::make_shared<Protagonista>(player))) << "Ho inserito personaggio dentro un muro";
	ASSERT_TRUE(livello.at(4, 4).setEntita(std::make_shared<Protagonista>(player))) << "Non ho inserito un personaggio dove potrebbe stare";
	ASSERT_TRUE(livello.at(5, 5).setEntita(std::make_shared<Attore>(monster))) << "Non ho inserito un attore dove potrebbe stare";
	ASSERT_EQ(-1, livello.muoviEntita(6, 6, 7, 4)) << "Ho provato a muovere qualcosa che non c'e'";
	ASSERT_EQ(-2, livello.muoviEntita(5, 5, 5, 5)) << "Ho provato a muovermi da un punto allo stesso punto";
	ASSERT_EQ(-3, livello.muoviEntita(5, 5, 5, 50)) << "L'arrivo era fuori dal piano ma mi sono mosso lo stesso";
	ASSERT_EQ(4, livello.muoviEntita(4, 4, 1, 1)) << "Ho terminato il movimento anche se era troppo lungo";
	//ASSERT_EQ("Personaggio", livello.at(3, 3).getEntita()->getNome()) << "Il movimento precedente mi ha condotto qui ma non c'e' nessuno";
	ASSERT_EQ(1, livello.muoviEntita(3, 3, 2, 2)) << "Mi sono spostato dentro un muro";
	ASSERT_EQ(0, livello.muoviEntita(3, 3, 4, 4)) << "Non mi sono mosso anche se potevo e dovevo";
	ASSERT_EQ(2, livello.muoviEntita(4, 4, 5, 5)) << "Ho tamponato un'altra entita' anche se non potevo";

}

TEST(TestPiano, TestPianoPerlinNoise) {
	bool tuttoBene=false;
	int counter=0;
	for (int i = 0; i < 100; i++) {
		pianoCavernaIsola pianoTest(20, 20);
		for (auto i = 0; i < 400; i++) {
			coord posizione(i % 20, i / 20);
			if (pianoTest.at(posizione).getEntita() != 0)
				tuttoBene = true;
		}
		if (tuttoBene = true)
			counter++;
	}
	ASSERT_EQ(counter, 100)<< "Non ho generato il protagonista in almeno qualche piano." << std::endl;
}

TEST(TestPiano, TestPianoFromFile) {
	bool ok;
	PianoFile file("mappaTest.txt", ok);
	EXPECT_TRUE(ok)<< "File non caricato"<< std::endl;
	Piano controllo(9, 6, std::vector<std::shared_ptr<Oggetto>>(), std::vector<std::shared_ptr<Entita>>());
	controllo.creaStanzaRettangolare(3, 2, 4, 3);
	controllo.at(coord(5, 4)).setEvento(1);
	EXPECT_EQ(file.at(5, 4).getEvento(), 1) << "Ci dovrebbero essere delle scale qui." << std::endl;
	for (int i = 0; i < 54; i++) {
		auto a = controllo.at(coord(i % 9, i / 9)).isMuro();
		auto b = file.at(coord(i % 9, i / 9)).isMuro();
		EXPECT_TRUE(a == b) << i << "\t" << a << "\t" << b;
	}
	
}