#include "stdafx.h"
#include "gtest/gtest.h"

#include "..\Nella oscura e pronda caverna\Oggetto.cpp"


TEST(TestOggetto, testConsistenzaConstruttore)
{
	Oggetto idolo(15., "Hatkanda", "L'oggetto di un film generico", 400);
	EXPECT_EQ(idolo.getPeso(), 15.);
}

TEST(TestOggetto, testInutile)
{

}
