#pragma once

#include <fstream>

#include "specificDestinationLoggerWriteInterface.h"

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
class BasicFileLogger : public FileLoggerInterface
{
    public:
        BasicFileLogger();
        virtual ~BasicFileLogger();

        // Non copyable& non moveable class
        BasicFileLogger(const BasicFileLogger& other) = delete;
        BasicFileLogger& operator=(const BasicFileLogger& rhs) = delete;
        BasicFileLogger(const BasicFileLogger&& other) = delete;
        BasicFileLogger& operator=(const BasicFileLogger&& rhs) = delete;

        // FileLogger interface API 
        virtual bool FileLoggerShouldRotateFile() const override;
        virtual void FileLoggerRotateFile() override;
        virtual void FileLoggerEnableDisableRotateFile(IN bool shouldRotateFile) override;

    protected:
        bool m_shouldRotateFile;
};

/*
This class holds implementation for a basic File logger. It inherites the basic logic from its
parent class and adds (mainly) the Observer API. Its objective is to write log messages to a file
in ths host file system.
NOTE: If an instance of this class that was created with file name "myFile.txt" is deleted and then
another object is created with the exact same name (and path) for the file name - the exising "fileName"
will be overwritten. By holding the file "handle" as a stack based std::ofstream class member, we assure
that whenever the FileLogger instance is deleted, the respective file will be closed (sort of RAII idiom).
*/
class FileLogger : public BasicFileLogger, public ILogMessageObserver
{
    public:
        explicit FileLogger(IN const std::string& fileName)
            : BasicFileLogger()
            , m_file(fileName)
        {

        }
        virtual ~FileLogger() {}

        // Non copyable& non movable class
        FileLogger(const FileLogger& other) = delete;
        FileLogger& operator=(const FileLogger& rhs) = delete;
        FileLogger(const FileLogger&& other) = delete;
        FileLogger& operator=(const FileLogger&& rhs) = delete;

         // Observer API
        void WriteLogMessage(const std::string& logMsg)
        {
            std::cout << "got log message:" << logMsg << std::endl;
            m_file << logMsg.c_str() << std::endl;
        }

    protected:
        std::ofstream m_file;
};

/*
The motivation behind having the StdoutFileLogger inherites as well from the BasicFileLogger
was due to the fact that essentially stdout is also a file. As of current implementation of it
and its parent, it does not "gain allot" from this inheritence, but if some relevant logic will be
added to the parent at later time, then he can benefit from it. Otherwise, this inheritance can be
eliminated.
*/
class StdoutFileLogger : public BasicFileLogger, public ILogMessageObserver
{
    public:
        StdoutFileLogger()
            : BasicFileLogger()
        {
            std::cout << "created StdoutFileLogger" << std::endl;
        }

        virtual ~StdoutFileLogger()
        {
            std::cout << "StdoutFileLogger::~StdoutFileLogger" << std::endl;
        }

         // Observer API
        void WriteLogMessage(const std::string& logMsg)
        {
            std::cout << logMsg << std::endl;
        }
};