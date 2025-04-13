#pragma once

#include <map>
#include <memory>
#include <mutex>

#include "include/myLoggerInterface.h"
#include "specificDestinationLoggerWriteInterface.h"

typedef std::pair<ILogMessageObserver*, bool> LoggerIsEnabledPair;

/*
This is the base class that holds implementation of the common functunalities for
any logger that will be used. It can be considerd as "loggers orchatrator".
By default it logs to stdout. If this output destination is not desired, it needs to
be manually disabled.
For each type logger type which is NOT stdout, BEFORE it can be enabled, a respective
object needs to be supplied. If a logger type is attempted to be enabled but there is
no such object, nothing will take place.

Implementation notes:
---------------------
The decision to have a map of observers is to be able to enable/disable them easily.
Note that because it is a map in which the key is the output
destination enum, so it is not possible to have several specific loggers from the same
type (for example, if the user wish to have two log files).
*/
class BasicLogger : public MyWriteToLoggInterface, public MyControlLogInterface, public ILogMessageSubject
{
    public:
        BasicLogger();
        explicit BasicLogger(IN const std::string& fileName);
        virtual ~BasicLogger();

        // Non copyable class
        BasicLogger(const BasicLogger& other) = delete;
        BasicLogger& operator=(const BasicLogger& rhs) = delete;
        
        // Log control APIs
        virtual void MyLoggerSetLogLevel(IN const enum MyLoggerLogLevel logLevelToSet) override;
        virtual void MyLoggerEnableOutputDestination(IN const enum MyLoggerOutputDestination outputDestination) override;
        virtual void MyLoggerDisableOutputDestination(IN const enum MyLoggerOutputDestination outputDestination) override;
        //virtual bool MyLoggerAddOutputDestinationLogger(IN ILogMessageObserver* loggerToAdd, IN const enum MyLoggerOutputDestination loggerType) override;

        // Subject APIs
        virtual void Attach(IN ILogMessageObserver* observer, IN const enum MyLoggerOutputDestination loggerType) override;
        virtual void Detach(IN ILogMessageObserver* observer, IN const enum MyLoggerOutputDestination loggerType) override;
        virtual void SendMessageToAllOutputDestinations(IN const std::string& logMsg) override;
        
        // Write to log APIs
        virtual void Error(IN const std::string& logMsg) override;
        virtual void Warn(IN const std::string& logMsg) override;
        virtual void Debug(IN const std::string& logMsg) override;
        virtual void Info(IN const std::string& logMsg) override;
        virtual void Info(IN std::string& logMsg, IN const std::string& text) override;


    protected:
        enum MyLoggerLogLevel m_currLogLevel;
        std::map<MyLoggerOutputDestination, LoggerIsEnabledPair> m_observersMap;

    private:
        mutable std::mutex mtx;
        bool shouldWriteLogMessage(IN const enum MyLoggerLogLevel msgLogLevel) const;
        bool disableEnableLogger(IN const enum MyLoggerOutputDestination outputDestination, IN const bool isToEnable);
};