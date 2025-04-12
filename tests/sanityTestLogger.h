#pragma once

#include <gtest/gtest.h>

#include "../src/logger/fileLogger.h"

TEST(SanityTestLogger, createFileOnlyLoggerWriteSingleInfoMessage_VerifyOnlyThisLineExists)
{ 
	std::cout << "==== START SanityTestLogger::createFileOnlyLoggerWriteSingleInfoMessage_VerifyOnlyThisLineExists ====" << std::endl;
    BasicFileLogger fileLogger("dsfsfd");
    bool retVal = fileLogger.FileLoggerShouldRotateFile();
    EXPECT_EQ(false, retVal);
    std::cout << "==== END SanityTestLogger::createFileOnlyLoggerWriteSingleInfoMessage_VerifyOnlyThisLineExists ====" << std::endl;
}
