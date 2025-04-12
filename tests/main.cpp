#include <iostream>
#include <gtest/gtest.h>

#include "sanityTestLogger.h"

using namespace std;

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	cout << "main - start of unit tests" << endl;
	return RUN_ALL_TESTS();
}
