#pragma once

#include <filesystem>
#include <gtest/gtest.h>

#include "../src/logger/fileLogger.h"
#include "../src/logger/memoryLogger.h"

const std::string g_testFileName = "testFile";

TEST(SanityTestLogger, createFileOnlyLoggerWriteSingleInfoMessage_VerifyOnlyThisLineExists)
{ 
	std::cout << "==== START SanityTestLogger::createFileOnlyLoggerWriteSingleInfoMessage_VerifyOnlyThisLineExists ====" << std::endl;
    const std::filesystem::path cwdPath= std::filesystem::current_path(); 
    std::cout << "Current working directory is:" << cwdPath.c_str() << std::endl;
    std::filesystem::path fullPath = cwdPath;
    fullPath /= g_testFileName;
    
    // Make sure there is no file from previous test/tests execution
    if (std::filesystem::exists(std::filesystem::path(fullPath.c_str())))
    {
        std::cout << "removing file from prev runs" << std::endl;
        std::remove(fullPath.c_str());
    }

    BasicFileLogger fileLogger(fullPath);

    // Make sure the file exists
    bool retVal = std::filesystem::exists(std::filesystem::path(fullPath));
    EXPECT_EQ(true, retVal);
    
    // Make sure the rotation logic is disabled
    retVal = fileLogger.FileLoggerShouldRotateFile();
    EXPECT_EQ(false, retVal);

    // Cleanup before terminating test
    if (std::filesystem::exists(std::filesystem::path(fullPath.c_str())))
    {
        std::cout << "removing file from current run" << std::endl;
        std::remove(fullPath.c_str());
    }
    
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
