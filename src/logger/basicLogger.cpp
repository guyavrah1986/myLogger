#include <iostream>

#include "basicLogger.h"
#include "fileLogger.h"

using namespace std;

BasicLogger::BasicLogger()
    : m_currLogLevel(MY_LOGGER_INFO)
{
    cout << "log level set to:" << m_currLogLevel << endl;
    auto stdoutObserver = new(StdoutFileLogger);
    this->Attach(stdoutObserver, MY_LOGGER_STDOUT);
    cout << "added logger type:" << MY_LOGGER_STDOUT << endl;
}

BasicLogger::BasicLogger(IN const string& fileName)
    : BasicLogger()
{
    cout << "about to add a BasicLogger that will log into file:" << fileName << endl;
    auto fileObserver = new FileLogger(fileName);
    this->Attach(fileObserver, MY_LOGGER_FILE);
    cout << "added logger type:" << MY_LOGGER_FILE << endl;
}

BasicLogger::~BasicLogger()
{
    cout << "about to remove all observers from the map" << endl;
    for (auto const&it : m_observersMap)
    {
        delete it.second.first;
    }

    cout << "done removing all observers from the map" << endl;
}

// ============================================================================
// Public methods:
// ============================================================================
void BasicLogger::MyLoggerSetLogLevel(IN const enum MyLoggerLogLevel logLevelToSet)
{
    lock_guard<mutex> lock(mtx);
    m_currLogLevel = logLevelToSet;
}

void BasicLogger::MyLoggerEnableOutputDestination(IN const enum MyLoggerOutputDestination outputDestination)
{
    lock_guard<mutex> lock(mtx);
    this->disableEnableLogger(outputDestination, true);
}

void BasicLogger::MyLoggerDisableOutputDestination(IN const enum MyLoggerOutputDestination outputDestination)
{
    lock_guard<mutex> lock(mtx);
    this->disableEnableLogger(outputDestination, false);
}

void BasicLogger::Attach(IN ILogMessageObserver* observer, IN const enum MyLoggerOutputDestination loggerType)
{
    lock_guard<mutex> lock(mtx);
    if (nullptr == observer)
    {
        cout << "got a NULL observer" << endl;
        return;
    }

    LoggerIsEnabledPair loggerToAddPair(observer, true);
    auto [it, b] = m_observersMap.try_emplace(loggerType, loggerToAddPair);
    if (false == b)
    {
        cout << "trying to add a logger of type:" << loggerType << " did not work, there is already one" << endl;
        return;
    }

    cout << "added logger of type:" << loggerType << endl;
}

void BasicLogger::Detach(IN const enum MyLoggerOutputDestination loggerType)
{
    lock_guard<mutex> lock(mtx);
    const auto& it = m_observersMap.find(loggerType);
    if (it == m_observersMap.end())
    {
        cout << "logger of type:" << loggerType << " does not exist, do not remove the provided logger" << endl;
        return;
    }

    delete it->second.first;
    m_observersMap.erase(it);
}

void BasicLogger::SendMessageToAllOutputDestinations(IN const string& logMsg)
{
    for (auto const& it : m_observersMap)
    {
        if (nullptr == it.second.first || false == it.second.second)
        {
            continue;
        }

        it.second.first->WriteLogMessage(logMsg);
    }
}

void BasicLogger::Error(IN const string& logMsg)
{
    lock_guard<mutex> lock(mtx);
    if (shouldWriteLogMessage(MY_LOGGER_ERROR))
    {
        this->SendMessageToAllOutputDestinations(logMsg);
    }
}

void BasicLogger::Error(IN string& logMsg, IN const string& text)
{
    lock_guard<mutex> lock(mtx);
    UtilsReplaceStrings(logMsg, m_curlyBracesTextReplacment, text);
    if (shouldWriteLogMessage(MY_LOGGER_ERROR))
    {
        this->SendMessageToAllOutputDestinations(logMsg);
    }
}

void BasicLogger::Warn(IN const string& logMsg)
{
    lock_guard<mutex> lock(mtx);
    if (shouldWriteLogMessage(MY_LOGGER_WARN))
    {
        this->SendMessageToAllOutputDestinations(logMsg);
    }
}

void BasicLogger::Warn(IN string& logMsg, IN const string& text)
{
    lock_guard<mutex> lock(mtx);
    UtilsReplaceStrings(logMsg, m_curlyBracesTextReplacment, text);
    if (shouldWriteLogMessage(MY_LOGGER_WARN))
    {
        this->SendMessageToAllOutputDestinations(logMsg);
    }
}

void BasicLogger::Debug(IN const string& logMsg)
{
    lock_guard<mutex> lock(mtx);
    if (shouldWriteLogMessage(MY_LOGGER_DEBUG))
    {
        this->SendMessageToAllOutputDestinations(logMsg);
    }
}

void BasicLogger::Debug(IN string& logMsg, IN const string& text)
{
    lock_guard<mutex> lock(mtx);
    UtilsReplaceStrings(logMsg, m_curlyBracesTextReplacment, text);
    if (shouldWriteLogMessage(MY_LOGGER_DEBUG))
    {
        this->SendMessageToAllOutputDestinations(logMsg);
    }
}

void BasicLogger::Info(IN const string& logMsg)
{
    lock_guard<mutex> lock(mtx);
    if (shouldWriteLogMessage(MY_LOGGER_INFO))
    {
        this->SendMessageToAllOutputDestinations(logMsg);
    }
}

void BasicLogger::Info(IN string& logMsg, IN const string& text)
{
    lock_guard<mutex> lock(mtx);
    UtilsReplaceStrings(logMsg, m_curlyBracesTextReplacment, text);
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

bool BasicLogger::disableEnableLogger(IN const enum MyLoggerOutputDestination outputDestination, IN const bool isToEnable)
{
    auto const& it = m_observersMap.find(outputDestination);
    if (it == m_observersMap.end())
    {
        cout << "the output destination type:" << outputDestination << ", is not present (make sure you initialized it)" << endl;
        return false;
    }

    LoggerIsEnabledPair& tmp = m_observersMap[outputDestination];
    if (nullptr == tmp.first)
    {
        cout << "the logger of type:" << outputDestination << " is NULL, aborting disabling it" << endl;
        return false;
    }

    tmp.second = isToEnable;
    cout << "set logger of type:" << outputDestination << " should print message to:" << isToEnable <<  endl;
    return true;
}
