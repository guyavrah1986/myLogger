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

/*
This is the very minium API that is needed write messages (in different verbosities).
It should be implemented by any object that wishes to "orchatrate" logging functunalities
and/or any object that wishes to have a customized tag.
*/
class MyWriteToLoggInterface
{
  public:
    virtual void Error(IN std::string& logMsg, IN const std::string& text="") = 0;
    virtual void Warn(IN std::string& logMsg, IN const std::string& text="") = 0;
    virtual void Debug(IN std::string& logMsg, IN const std::string& text="") = 0;
    virtual void Info(IN std::string& logMsg, IN const std::string& text="") = 0;
};

/*
This interface objective is to enable the client of the logger to set it according to its needs.
*/
class MyControlLogInterface
{
  public:
    virtual void MyLoggerSetLogLevel(IN const enum MyLoggerLogLevel logLevelToSet) = 0;
    virtual void MyLoggerEnableOutputDestination(IN const enum MyLoggerOutputDestination outputDestination) = 0;
    virtual void MyLoggerDisableOutputDestination(IN const enum MyLoggerOutputDestination outputDestination) = 0;
};