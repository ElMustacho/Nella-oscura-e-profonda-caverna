#include "pch.h"
#include "..\Nella oscura e pronda caverna\Oggetto.h"
#include "..\Nella oscura e pronda caverna\Oggetto.cpp"
#include <string>
#include <iostream>

int main(int argc, char* argv[]) 
{
	testing::InitGoogleTest(&argc, argv);
	auto garbage = RUN_ALL_TESTS();
	char c;
	std::cin >> c;
}

TEST(TestOggetti, testConsistenzaConstruttore) {
	Oggetto idolo(15., "Hatkanda", "L'oggetto di un film generico", 400);
	EXPECT_EQ(idolo.getPeso(),15.);
}