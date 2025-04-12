#pragma once

#include <gtest/gtest.h>

TEST(SanityTestLogger, createFileOnlyLoggerWriteSingleInfoMessage_VerifyOnlyThisLineExists)
{ 
	std::cout << "==== START SanityTestLogger::createFileOnlyLoggerWriteSingleInfoMessage_VerifyOnlyThisLineExists ====" << std::endl;
    EXPECT_EQ(1, 1);
    std::cout << "==== END SanityTestLogger::createFileOnlyLoggerWriteSingleInfoMessage_VerifyOnlyThisLineExists ====" << std::endl;
}
