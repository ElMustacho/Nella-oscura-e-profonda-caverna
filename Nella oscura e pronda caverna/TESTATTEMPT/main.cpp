

#include "stdafx.h"
#include <iostream>

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	int a;
	std::cin >> a;
}

