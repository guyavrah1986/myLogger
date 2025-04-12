#include <iostream>
#include <gtest/gtest.h>

#include "sanityTestLogger.h"

using namespace std;

// This is the entry point for all GTest based unit tests
int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	cout << "main - start of unit tests" << endl;
	return RUN_ALL_TESTS();
}
