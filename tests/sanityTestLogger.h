#pragma once

#include <gtest/gtest.h>

#include "../src/logger/fileLogger.h"
#include "../src/logger/memoryLogger.h"

TEST(SanityTestLogger, createFileOnlyLoggerWriteSingleInfoMessage_VerifyOnlyThisLineExists)
{ 
	std::cout << "==== START SanityTestLogger::createFileOnlyLoggerWriteSingleInfoMessage_VerifyOnlyThisLineExists ====" << std::endl;
    BasicFileLogger fileLogger("dsfsfd");
    bool retVal = fileLogger.FileLoggerShouldRotateFile();
    EXPECT_EQ(false, retVal);
    std::cout << "==== END SanityTestLogger::createFileOnlyLoggerWriteSingleInfoMessage_VerifyOnlyThisLineExists ====" << std::endl;
}

TEST(SanityTestLogger, createMemoryOnlyLoggerWriteSingleInfoMessage_VerifyOnlyThisLineExists)
{ 
	std::cout << "==== START SanityTestLogger::createMemoryOnlyLoggerWriteSingleInfoMessage_VerifyOnlyThisLineExists ====" << std::endl;
    BasicMemoryLogger memLogger;
    bool retVal = memLogger.MemoryLoggerIsAbleWriteToMemory();
    EXPECT_EQ(true, retVal);
    std::cout << "==== END SanityTestLogger::createMemoryOnlyLoggerWriteSingleInfoMessage_VerifyOnlyThisLineExists ====" << std::endl;
}
