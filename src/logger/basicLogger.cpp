#include <iostream>

#include "basicLogger.h"
#include "fileLogger.h"

using namespace std;

BasicLogger::BasicLogger()
    : m_currLogLevel(MY_LOGGER_INFO)
{
    // The defualt ctor created the stdout logger type 
    // It also set the log level to INFO
    auto stdoutObserver = new(StdoutFileLogger);
    this->Attach(stdoutObserver, MY_LOGGER_STDOUT);
}

BasicLogger::~BasicLogger()
{
    cout << "about to remove all observers from the map" << endl;
    for (auto const&it : m_observersMap)
    {
        if (it.first == MY_LOGGER_STDOUT)
        {
            delete it.second;
        }

        cout << "erasing observer of type:" << it.first << endl;
        m_observersMap.erase(it.first);
    }
}

void BasicLogger::MyLoggerSetLogLevel(IN const enum MyLoggerLogLevel logLevelToSet)
{
    m_currLogLevel = logLevelToSet;
}

void BasicLogger::MyLoggerEnableOutputDestination(IN const enum MyLoggerOutputDestination outputDestination)
{
    // Call the Subject Attach API
    if (MY_LOGGER_STDOUT == outputDestination)
    {
        // here we only need to actually enable it
        return;
    }

    // In the other types of output destinations, we need to make sure that 
    // indeed there is the respective ILogMessageObserver object, if not, print
    // a message and return false ("error")
}

void BasicLogger::MyLoggerDisableOutputDestination(IN const enum MyLoggerOutputDestination outputDestination)
{
    if (m_observersMap.find(outputDestination) == m_observersMap.end())
    {
        cout << "the output destination type:" << outputDestination << ", is not present (make sure you initialized it)" << endl;
        return;
    }
}

/*
This method enables the client of this class to add a new customized logger of its own.
It returns true if the logger provided was added successfully, false otherwise.

bool BasicLogger::MyLoggerAddOutputDestinationLogger(IN ILogMessageObserver* loggerToAdd, IN const enum MyLoggerOutputDestination loggerType)
{
    if (nullptr == loggerToAdd)
    {
        cout << "logger of type:" << loggerType << " providied is NULL, does not add it" << endl;
        return false;
    }


}
*/

void BasicLogger::Attach(IN ILogMessageObserver* observer, IN const enum MyLoggerOutputDestination loggerType)
{
    if (nullptr == observer)
    {
        cout << "got a NULL observer" << endl;
        return;
    }

    auto [it, b] = m_observersMap.try_emplace(loggerType, observer);
    if (false == b)
    {
        cout << "trying to add a logger of type:" << loggerType << " did not work, there is already one" << endl;
        return;
    }

    cout << "added logger of type:" << loggerType << endl;
}

void BasicLogger::Detach(IN ILogMessageObserver* observer, IN const enum MyLoggerOutputDestination loggerType)
{
    const auto it = m_observersMap.find(loggerType);
    if (it == m_observersMap.end())
    {
        cout << "logger of type:" << loggerType << " does not exist, do not remove the provided logger" << endl;
        return;
    }
    else if (it->second != observer)
    {
        cout << "logger of type:" << loggerType << " exists, but the provided one is not the one in the map" << endl;
        return;
    }

    // remove it from map
    // TODO: if normal pointer - need to delete it before!!
    m_observersMap.erase(it);
}

void BasicLogger::SendMessageToAllOutputDestinations(IN const string& logMsg)
{
    for (auto const& it : m_observersMap)
    {
        it.second->WriteLogMessage(logMsg);
    }
}

void BasicLogger::Error(IN const string& logMsg)
{
    if (shouldWriteLogMessage(MY_LOGGER_ERROR))
    {
        this->SendMessageToAllOutputDestinations(logMsg);
    }
}

void BasicLogger::Warn(IN const std::string& logMsg)
{
    if (shouldWriteLogMessage(MY_LOGGER_WARN))
    {
        this->SendMessageToAllOutputDestinations(logMsg);
    }
}

void BasicLogger::Debug(IN const std::string& logMsg)
{
    if (shouldWriteLogMessage(MY_LOGGER_DEBUG))
    {
        this->SendMessageToAllOutputDestinations(logMsg);
    }
}

void BasicLogger::Info(IN const std::string& logMsg)
{
    if (shouldWriteLogMessage(MY_LOGGER_INFO))
    {
        this->SendMessageToAllOutputDestinations(logMsg);
    }
}

// ============================================================================
// Private methods:
// ============================================================================
bool BasicLogger::shouldWriteLogMessage(IN const enum MyLoggerLogLevel msgLogLevel) const
{
    if (msgLogLevel <= m_currLogLevel)
    {
        return true;
    }

    return false;
}
