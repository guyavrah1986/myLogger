#pragma once

#include <filesystem>
#include <sstream>

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

    {
        FileLogger fileLogger(fullPath);
        bool retVal = std::filesystem::exists(std::filesystem::path(fullPath));
        EXPECT_EQ(true, retVal);
        
        // Make sure the rotation logic is disabled
        retVal = fileLogger.FileLoggerShouldRotateFile();
        EXPECT_EQ(false, retVal);
    
        // Write one line to the file
        const std::string logMsg = "this is line 1";
        fileLogger.WriteLogMessage(logMsg);
    
        // Make sure this line is the first line in the file
        #include <fstream>
        std::ifstream infile(fullPath);
        std::string line;
        size_t numLines = 0;
        while (std::getline(infile, line))
        {
            if (!line.empty() && line[line.length()-1] == '\n') {
                line.erase(line.length()-1);
            }

            std::istringstream iss(line);
            ++numLines;
            std::cout << "line:[" << numLines << "]:" << line << std::endl; 
        }
    
        EXPECT_EQ(true, numLines == 1);
        //EXPECT_EQ(line.compare(logMsg), 0);

        // Now write a log line with the text support flavour API
        
    }

    // Cleanup before terminating test
    if (std::filesystem::exists(std::filesystem::path(fullPath.c_str())))
    {
        std::cout << "removing file from current run" << std::endl;
        std::remove(fullPath.c_str());
    }
    
    std::cout << "==== END SanityTestLogger::createFileOnlyLoggerWriteSingleInfoMessage_VerifyOnlyThisLineExists ====" << std::endl;
}

TEST(SanityTestLogger, createStdoutLoggerWriteSingleInfoMessage_VerifyOnlyThisLineExists)
{ 
	std::cout << "==== START SanityTestLogger::createStdoutLoggerWriteSingleInfoMessage_VerifyOnlyThisLineExists ====" << std::endl;
    StdoutFileLogger stdoutLogger;
    
    // Make sure the rotation logic is disabled
    bool retVal = stdoutLogger.FileLoggerShouldRotateFile();
    EXPECT_EQ(false, retVal);

    // Write single log message
    const std::string logMsg = "this is a message to cout";
    stdoutLogger.WriteLogMessage(logMsg);
    std::cout << "==== END SanityTestLogger::createStdoutLoggerWriteSingleInfoMessage_VerifyOnlyThisLineExists ====" << std::endl;
}

TEST(SanityTestLogger, createMemoryOnlyLoggerWriteSingleInfoMessage_VerifyOnlyThisLineExists)
{ 
	std::cout << "==== START SanityTestLogger::createMemoryOnlyLoggerWriteSingleInfoMessage_VerifyOnlyThisLineExists ====" << std::endl;
    BasicMemoryLogger memLogger;
    const std::string msg1 = "this is the 1st message";
    bool retVal = memLogger.MemoryLoggerIsAbleWriteToMemory(msg1);
    EXPECT_EQ(true, retVal);
    std::cout << "==== END SanityTestLogger::createMemoryOnlyLoggerWriteSingleInfoMessage_VerifyOnlyThisLineExists ====" << std::endl;
}
