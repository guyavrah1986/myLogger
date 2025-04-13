#pragma once

#include "include/myLoggerInterface.h"

class ILogMessageObserver
{
    public:
        virtual ~ILogMessageObserver(){};
        virtual void WriteLogMessage(IN const std::string& logMsg) = 0;
};
   
class ILogMessageSubject
{
    public:
        virtual ~ILogMessageSubject(){};
        virtual void Attach(IN ILogMessageObserver* observer, IN const enum MyLoggerOutputDestination loggerType) = 0;
        virtual void Detach(IN ILogMessageObserver* observer, IN const enum MyLoggerOutputDestination loggerType) = 0;
        virtual void SendMessageToAllOutputDestinations(IN const std::string& logMsg) = 0;
};