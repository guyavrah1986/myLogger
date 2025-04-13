#pragma once

#include "../../utils/utils.h"

enum MyLoggerLogLevel
{
  MY_LOGGER_ERROR = 0,
  MY_LOGGER_WARN,
  MY_LOGGER_DEBUG,
  MY_LOGGER_INFO
};

enum MyLoggerOutputDestination
{
  MY_LOGGER_STDOUT = 0,
  MY_LOGGER_FILE,
  MY_LOGGER_MEMORY
};

class MyLoggerInterface
{
  public:
    // Initialization APIs

    // Log control APIs
    virtual void MyLoggerSetLogLevel(IN const enum MyLoggerLogLevel logLevelToSet) = 0;
    virtual void MyLoggerEnableOutputDestination(IN const enum MyLoggerOutputDestination outputDestination) = 0;
    virtual void MyLoggerDisableOutputDestination(IN const enum MyLoggerOutputDestination outputDestination) = 0;
    //virtual bool MyLoggerAddOutputDestinationLogger(IN ILogMessageObserver* loggerToAdd, IN const enum MyLoggerOutputDestination loggerType) = 0;
      
    // Write to log APIs
    virtual void Error(IN const std::string& logMsg) = 0;
    virtual void Warn(IN const std::string& logMsg) = 0;
    virtual void Debug(IN const std::string& logMsg) = 0;
    virtual void Info(IN const std::string& logMsg) = 0;
};