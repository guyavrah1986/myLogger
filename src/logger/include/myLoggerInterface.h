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

 protected:     
      // Different write destination APIs.
      // The other two destination options are set with their
      // own interface.
      virtual void MyLoggerWriteToStd(IN const std::string& logMsg) = 0;   
};

/* 
The purpose of this interface is to be able to add (if desired) some "extra"
logic that should be taken into account when writing log messages to the 
memory.
*/
class MyMemoryLoggerInterface
{
  public:
    virtual void MyMemoryLoggerWriteToMemory(IN const std::string& logMsg) = 0;
    virtual bool MyMemoryLoggerIsAbleWriteToMemory() = 0;
    virtual void MyMemoryLoggerFlushMemory() = 0;
};