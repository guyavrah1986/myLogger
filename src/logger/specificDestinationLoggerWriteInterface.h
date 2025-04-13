#pragma once

#include <string>

class ILogMessageObserver
{
    public:
        virtual ~ILogMessageObserver(){};
        virtual void WriteLogMessage(const std::string& logMsg) = 0;
};
   
class ILogMessageSubject
{
    public:
        virtual ~ILogMessageSubject(){};
        virtual void Attach(ILogMessageObserver* observer) = 0;
        virtual void Detach(ILogMessageObserver* observer) = 0;
        virtual void SendMessageToAllOutputDestinations() = 0;
};