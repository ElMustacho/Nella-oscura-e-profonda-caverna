// TESTATTEMPT.cpp : definisce il punto di ingresso dell'applicazione console.
//

#include "stdafx.h"
#include <iostream>

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	int a;
	std::cin >> a;
}

