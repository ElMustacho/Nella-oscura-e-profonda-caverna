#include "stdafx.h"
#include "gtest/gtest.h"

#include "..\Nella oscura e pronda caverna\Entita.cpp"
#include "..\Nella oscura e pronda caverna\Attributi.cpp"


TEST(TestEntita, testConsistenzaCostruttore)
{
	Entita player1("Pippo", Attributi(1, 2, 3, 4, 5, 6, 7, 8));
	EXPECT_EQ(player1.getNome(), "Pippo");
}