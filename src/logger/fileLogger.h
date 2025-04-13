#pragma once

#include <string>
#include <fstream>

#include "specificDestinationLoggerWriteInterface.h"
#include "../utils/utils.h"

/* 
The purpose of this interface is to be able to add/modify (if desired) some "extra"/current
logic that should be taken into account when writing log messages to the a file.
*/
class FileLoggerInterface
{
  public:
    /*
    This API is used to check whether or not log rotation is desired.
    */
    virtual bool FileLoggerShouldRotateFile() const = 0;
    
    /*
    This is an "extra" logic (capability) that the file logger can provide.
    When the log file of the application is being "monitored" by tools such as
    Linux's logrotate, then providing an actual implementation for this API is
    redundeant. Otherwise, if the developer of the application wishes to have full
    control over the rotation mechanism - then one can do so by adding it to this API.
    */
    virtual void FileLoggerRotateFile() = 0;
    
    /*
    This API is used to enable/disable file rotation at run-time. In case modifying
    this option is not an option, this API can be removed.
    */
    virtual void FileLoggerEnableDisableRotateFile(IN bool shouldRotateFile) = 0;
};

/*
This class is the most simple implementation for the file logging capabilities.
It does not add any sophisticated logic/mechanism to the file rotation, which makes 
it a good candidate for the stdout logger and also for a regular file (on host file
system) that does not wish to have file rotation capabilities (for example, if the
application is set to have its log rotate by the logrotate utility in Linux).
The file itself is kept using the std::ofstream as a class member, thus leveraging
its inherent RAII implementation. 
*/
class BasicFileLogger : public FileLoggerInterface, ILogMessageObserver
{
    public:
        explicit BasicFileLogger(IN const std::string& fileName);
        virtual ~BasicFileLogger();

        // Non copiable class
        BasicFileLogger(const BasicFileLogger& other) = delete;
        BasicFileLogger& operator=(const BasicFileLogger& rhs) = delete;

        // FileLogger interface API 
        virtual bool FileLoggerShouldRotateFile() const override;
        virtual void FileLoggerRotateFile() override;
        virtual void FileLoggerEnableDisableRotateFile(IN bool shouldRotateFile) override;

        // Observer API
        virtual void WriteLogMessage(const std::string& logMsg) override;

    protected:
        bool m_shouldRotateFile;
        std::ofstream m_file;
};