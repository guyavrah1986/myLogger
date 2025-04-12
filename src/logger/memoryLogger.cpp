#include <iostream>

#include "memoryLogger.h"

using namespace std;

BasicMemoryLogger::BasicMemoryLogger()
{

}

BasicMemoryLogger::~BasicMemoryLogger()
{

}

void BasicMemoryLogger::MemoryLoggerWriteToMemory(IN const string& logMsg)
{
    cout << "got log message:" << logMsg << endl;
}

bool BasicMemoryLogger::MemoryLoggerIsAbleWriteToMemory() const
{
    return true;
}

void BasicMemoryLogger::MemoryLoggerFlushMemory()
{

}