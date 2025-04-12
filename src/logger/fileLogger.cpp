#include "fileLogger.h"

using namespace std;

BasicFileLogger::BasicFileLogger(IN const string& fileName)
{

}

BasicFileLogger::~BasicFileLogger()
{

}

void BasicFileLogger::FileLoggerWriteToFile(IN const string& logMsg)
{

}

bool BasicFileLogger::FileLoggerShouldRotateFile() const
{
    return false;
}

void BasicFileLogger::FileLoggerRotateFile()
{
    // this function does not do anything
}

void BasicFileLogger::FileLoggerEnableDisableRotateFile(IN bool shouldRotateFile)
{
    this->m_shouldRotateFile = shouldRotateFile;
}