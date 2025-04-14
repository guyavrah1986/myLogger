#pragma once

#include "include/myLoggerInterface.h"

/*
This interface is to facilitate a unified "entry" point to write a log message. By implementing it
the object that does so, registers itself to be a "legitimate output destination" witihn the logger
"bank" of different outputs (file/console/memory...).
*/
class ILogMessageObserver
{
    public:
        virtual ~ILogMessageObserver(){};
        virtual void WriteLogMessage(IN const std::string& logMsg) = 0;
};

/*
This interface "completes" the Observer mechanism with the above interface. It is to be used by any class
that aims to be the "log orchastrator", thus enabling different output destinations to regiters themselves
within it.
*/
class ILogMessageSubject
{
    public:
        virtual ~ILogMessageSubject(){};
        virtual void Attach(IN ILogMessageObserver* observer, IN const enum MyLoggerOutputDestination loggerType) = 0;
        virtual void Detach(IN const enum MyLoggerOutputDestination loggerType) = 0;
        virtual void SendMessageToAllOutputDestinations(IN const std::string& logMsg) = 0;
};