#pragma once

#include <string>

#include "../../utils/utils.h"

enum MyLoggerLogLevel
{
  ERROR = 0,
  WARN,
  DEBUG,
  INFO
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
      // Log control APIs
      virtual bool MyLoggerSetLogLevel(IN const enum MyLoggerLogLevel) = 0;
      virtual void MyLoggerEnableOutputDestination(IN const enum MyLoggerOutputDestination) = 0;
      virtual void MyLoggerDisableOutputDestination(IN const enum MyLoggerOutputDestination) = 0;
      
      // Write to log APIs
      virtual void Error(IN const std::string& logMsg) = 0;
      virtual void Warn(IN const std::string& logMsg) = 0;
      virtual void Debug(IN const std::string& logMsg) = 0;
      virtual void Info(IN const std::string& logMsg) = 0;
};