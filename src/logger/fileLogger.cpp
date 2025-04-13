#include <iostream>

#include "fileLogger.h"

using namespace std;

BasicFileLogger::BasicFileLogger(IN const string& fileName)
    : m_shouldRotateFile(false)
    , m_file(fileName)
{
    cout << "got file name:" << fileName << endl;
}

BasicFileLogger::~BasicFileLogger()
{

}

void BasicFileLogger::WriteLogMessage(const std::string& logMsg)
{
    cout << "got log message:" << logMsg << endl;
    m_file << logMsg.c_str() << endl;
}

bool BasicFileLogger::FileLoggerShouldRotateFile() const
{
    return this->m_shouldRotateFile;
}

void BasicFileLogger::FileLoggerRotateFile()
{
    // This function does not do anything
}

void BasicFileLogger::FileLoggerEnableDisableRotateFile(IN bool shouldRotateFile)
{
    this->m_shouldRotateFile = shouldRotateFile;
}