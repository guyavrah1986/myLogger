#pragma once

#include <memory>

#include "include/myLoggerInterface.h"
#include "fileLogger.h"

/*
This is the base class that holds implementation of the common functunalities for
any logger that will be used. It can be considerd as "loggers orchatrator".
By default and unless specified otherwise, it logs to stdout.
*/
class BasicLogger : public MyLoggerInterface
{
    public:
        BasicLogger();
        virtual ~BasicLogger();

        // Non copyable class
        BasicLogger(const BasicLogger& other) = delete;
        BasicLogger& operator=(const BasicLogger& rhs) = delete;
        

        // Log control APIs
        virtual bool MyLoggerSetLogLevel(IN const enum MyLoggerLogLevel) override;
        virtual void MyLoggerEnableOutputDestination(IN const enum MyLoggerOutputDestination) override;
        virtual void MyLoggerDisableOutputDestination(IN const enum MyLoggerOutputDestination) override;
        
        // Write to log APIs
        virtual void Error(IN const std::string& logMsg) override;
        virtual void Warn(IN const std::string& logMsg) override;
        virtual void Debug(IN const std::string& logMsg) override;
        virtual void Info(IN const std::string& logMsg) override;

    protected:
        enum MyLoggerLogLevel m_currLogLevel;
        std::unique_ptr<FileLoggerInterface> m_stdoutLogger;
};