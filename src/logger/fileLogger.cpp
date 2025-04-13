#include <iostream>

#include "fileLogger.h"

using namespace std;

BasicFileLogger::BasicFileLogger()
    : m_shouldRotateFile(false)
{

}

BasicFileLogger::~BasicFileLogger()
{

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