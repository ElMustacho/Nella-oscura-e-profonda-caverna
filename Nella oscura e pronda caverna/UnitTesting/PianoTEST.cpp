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

TEST(TestPiano, CostruzioneStanzaGeneratore1) {
	std::vector<Oggetto> tabellaLoot; //VUOTA
	std::vector<Entita> tabellaEntita; //VUOTA
	Piano livelloTest(10, 8, 1, tabellaLoot, tabellaEntita);
	EXPECT_FALSE(livelloTest.creaStanzaRettangolare(0, 0, 15, 15))<<"Stanza troppo grande";
	EXPECT_TRUE(livelloTest.creaStanzaRettangolare(4, 4, 3, 2))<<"Stanza correttamente inserita";
	EXPECT_FALSE(livelloTest.creaStanzaRettangolare(3, 3, 4, 4))<<"Stanza non inserita perché sovrapposta";
}