#pragma once
#include "stdafx.h"
#include "gtest/gtest.h"

#include "..\Nella oscura e pronda caverna\Entita.cpp"
#include "..\Nella oscura e pronda caverna\Danno.cpp"
#include "..\Nella oscura e pronda caverna\Oggetto.cpp"
#include "..\Nella oscura e pronda caverna\Attributi.cpp"

/* TEST Entita */

TEST(TestEntita, testConsistenzaCostruttore)
{
	std::vector<Oggetto> oggetti;
	Entita player1("Pippo", oggetti, Attributi(1, 2, 3, 4, 5, 6, 7, 8), oggetti);
	EXPECT_EQ(player1.getNome(), "Pippo");
}

/* TEST Oggetto */

TEST(TestOggetto, testConsistenzaConstruttore)
{
	Oggetto idolo(15., "Hatkanda", "L'oggetto di un film generico", 400);
	EXPECT_EQ(idolo.getPeso(), 15.);
}