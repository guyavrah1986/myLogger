#include <iostream>

#include "memoryLogger.h"

using namespace std;

BasicMemoryLogger::BasicMemoryLogger()
{
    cout << "BasicMemoryLogger::BasicMemoryLogger - setting max buffer size to:" << MAX_BUFF_SIZE << endl;
    m_memBuff.reserve(MAX_BUFF_SIZE);
}

BasicMemoryLogger::~BasicMemoryLogger()
{
    m_memBuff.clear();
}

void BasicMemoryLogger::WriteLogMessage(IN const string& logMsg)
{
    if (false == MemoryLoggerIsAbleWriteToMemory(logMsg))
    {
        cout << "message:" << logMsg << ", can fit into the memory buffer" << endl;
        return;
    }

    copy(logMsg.begin(), logMsg.end(), back_inserter(m_memBuff));
}

bool BasicMemoryLogger::MemoryLoggerIsAbleWriteToMemory(IN const string& logMsg) const
{
    if (m_memBuff.size() + logMsg.length() > m_memBuff.capacity())
    {
        return false;
    }

    return true;
}

void BasicMemoryLogger::MemoryLoggerFlushMemory()
{
    m_memBuff.clear();
}