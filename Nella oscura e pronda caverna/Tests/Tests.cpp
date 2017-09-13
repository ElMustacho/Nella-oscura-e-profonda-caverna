#pragma once

#include "stdafx.h"
#include "gtest/gtest.h"

#include "..\Nella oscura e pronda caverna\Entita.cpp"
#include "..\Nella oscura e pronda caverna\Danno.cpp"
#include "..\Nella oscura e pronda caverna\Oggetto.cpp"
#include "..\Nella oscura e pronda caverna\Attributi.cpp"
#include "Tests.h"

/* TEST Entita */

TEST(TestEntita, testConsistenzaCostruttore)
{
	std::list<std::shared_ptr<Oggetto>> oggetti1;
	std::vector<std::shared_ptr<Oggetto>> oggetti2;
	Entita player1( "Pippo", oggetti1, Attributi(1, 2, 3, 4, 5, 6, 7, 8), oggetti2 );
	EXPECT_EQ(player1.getNome(), "Pippo");
}

/* TEST Oggetto */

TEST(TestOggetto, testConsistenzaConstruttore)
{
	Oggetto idolo(15., "Hatkanda", "L'oggetto di un film generico", 400);
	EXPECT_EQ(idolo.getPeso(), 15.);
}