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
be manually disabled after the instance of this class is instaniated.
For each logger type which is NOT stdout, BEFORE it can be enabled, a respective
object needs to be supplied. If a logger type is attempted to be enabled but there is
no such object, nothing will take place.

Implementation notes:
---------------------
1) The decision to have a map of observers is to be able to enable/disable them easily.
Note that because it is a map in which the key is the output
destination enum, it is not possible to have several loggers from the same
type (for example, if the user wish to have two log files).
2) To enable the user (client) of this class to add (and remove) its "own" loggers of choice, the
Attach&Detach APIs were added. They have a mutex.lock within each one of them. In addition and for
simplicty, in each one of the constructors of this class, there is one logger that is "implictly"
created for the user. If we were to add a mutex.lock there as well, we will encounter a deadlock --> the
assumption is that any of the two constructors of this class will NOT be called from several threads at
the same time. If this is a hard thing to ask, then these ctors need to be changed so that they WON'T create
logger within them, thus the user will have to create them himself.
*/
class BasicLogger : public MyWriteToLoggInterface, public MyControlLogInterface, public ILogMessageSubject
{
    public:
        BasicLogger();
        explicit BasicLogger(IN const std::string& fileName);
        virtual ~BasicLogger();

        // Non copyable& non movable
        BasicLogger(const BasicLogger& other) = delete;
        BasicLogger& operator=(const BasicLogger& rhs) = delete;
        BasicLogger(const BasicLogger&& other) = delete;
        BasicLogger& operator=(const BasicLogger&& rhs) = delete;
        
        // Log control APIs
        virtual void MyLoggerSetLogLevel(IN const enum MyLoggerLogLevel logLevelToSet) override;
        virtual void MyLoggerEnableOutputDestination(IN const enum MyLoggerOutputDestination outputDestination) override;
        virtual void MyLoggerDisableOutputDestination(IN const enum MyLoggerOutputDestination outputDestination) override;

        // Subject APIs
        virtual void Attach(IN ILogMessageObserver* observer, IN const enum MyLoggerOutputDestination loggerType) override;
        virtual void Detach(IN const enum MyLoggerOutputDestination loggerType) override;
        virtual void SendMessageToAllOutputDestinations(IN const std::string& logMsg) override;
        
        // Write to log APIs
        virtual void Error(IN std::string& logMsg, IN const std::string& text="") override;
        virtual void Warn(IN std::string& logMsg, IN const std::string& text="") override;
        virtual void Debug(IN std::string& logMsg, IN const std::string& text="") override;
        virtual void Info(IN std::string& logMsg, IN const std::string& text="") override;

    protected:
        enum MyLoggerLogLevel m_currLogLevel;
        std::map<MyLoggerOutputDestination, LoggerIsEnabledPair> m_observersMap;

    private:
        mutable std::mutex mtx;
        static constexpr std::string m_curlyBracesTextReplacment = "{}";
        bool shouldWriteLogMessage(IN const enum MyLoggerLogLevel msgLogLevel) const;
        bool disableEnableLogger(IN const enum MyLoggerOutputDestination outputDestination, IN const bool isToEnable);
};