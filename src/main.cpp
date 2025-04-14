#include <filesystem>
#include <iostream>

#include "logger/basicLogger.h"
#include "logger/memoryLogger.h"

using namespace std;

class SampleClassWithBasicLog : public MyWriteToLoggInterface
{
	public:
		SampleClassWithBasicLog()
		{
			cout << "SampleClassWithBasicLog::SampleClassWithBasicLog" << endl;
		}

		~SampleClassWithBasicLog()
		{
			cout << "SampleClassWithBasicLog::~SampleClassWithBasicLog" << endl;
		}

		void someFunc()
		{
			const string msg = "some message";
			Info(msg);
		}

		void someFuncThatWriteTextFormatMessage()
		{
			string msg = "hello {}";
			const string text = "world";
			Info(msg, text);
		}

		void InitLog(MyWriteToLoggInterface* logger)
		{
			this->m_classLogger = logger;
		}

		virtual void Error(IN const string& logMsg) override
		{
			m_classLogger->Error(m_classLogPrefix + logMsg);
		}

		virtual void Error(IN string& logMsg, IN const string& text) override
		{
			string newMsg = m_classLogPrefix + logMsg;
			m_classLogger->Error(newMsg, text);
		}

		virtual void Warn(IN const string& logMsg) override
		{
			m_classLogger->Warn(m_classLogPrefix + logMsg);
		}
		
		virtual void Warn(IN string& logMsg, IN const string& text) override
		{
			string newMsg = m_classLogPrefix + logMsg;
			m_classLogger->Warn(newMsg, text);
		}

		virtual void Debug(IN const string& logMsg) override
		{
			m_classLogger->Debug(m_classLogPrefix +  logMsg);
		}
		
		virtual void Debug(IN string& logMsg, IN const string& text) override
		{
			string newMsg = m_classLogPrefix + logMsg;
			m_classLogger->Debug(newMsg, text);
		}

		virtual void Info(IN const string& logMsg) override
		{
			m_classLogger->Info(m_classLogPrefix + logMsg);
		}
        
		virtual void Info(IN string& logMsg, IN const string& text) override
		{
			string newMsg = m_classLogPrefix + logMsg;
			m_classLogger->Info(newMsg, text);
		}

	private:
		const string m_classLogPrefix = "SampleClassWithBasicLog:";
		MyWriteToLoggInterface* m_classLogger;
};

void createLoggerForStdoutOnlyExample()
{
	const string funcName = "createLoggerForStdoutOnlyExample - ";
	cout << funcName + "START" << endl;

	// By default the BasicLogger outputs message only to stdout
	// and is set to log level INFO
	BasicLogger basicLogger;
	string logMsg = "this is the first log message";
	basicLogger.Info(logMsg);
	basicLogger.MyLoggerSetLogLevel(MY_LOGGER_DEBUG);
	logMsg = "this message should NOT be printed";
	basicLogger.Info(logMsg);
	logMsg = "this message would be printed";
	basicLogger.Error(logMsg);
	cout << funcName + "END" << endl;
}

void createLoggerForStdoutAndFileExample()
{
	const string funcName = "createLoggerForStdoutAndFileExample - ";
	cout << funcName + "START" << endl;
	const string fileName = "exampleFile.txt";
	const filesystem::path cwdPath= std::filesystem::current_path(); 
    cout << funcName + "current working directory is:" << cwdPath.c_str() << endl;
    filesystem::path fullPath = cwdPath;
    fullPath /= fileName;
	cout << funcName + "creating logger for both stdout and file:" << fullPath.c_str() << endl;
	
	// Make sure there is no file from previous execution
	if (filesystem::exists(filesystem::path(fullPath.c_str())))
	{
		cout << "removing file:" << fullPath.c_str() << " from prev runs" << endl;
		remove(fullPath.c_str());
	}

	string fullFileName(fullPath.c_str());
	BasicLogger stdoutAndFileLogger(fullFileName);
	string logMsg = "this is the first log message, it will be printed to console and to file:" + fullFileName;
	stdoutAndFileLogger.Info(logMsg);
	
	// Now disable the file log and make sure the next message 
	// is NOT written to it but ONLY to stdout
	stdoutAndFileLogger.MyLoggerDisableOutputDestination(MY_LOGGER_FILE);
	logMsg = "this message will NOT be printed to file:" + fullFileName;
	stdoutAndFileLogger.Info(logMsg);

	// Now enable back the file logger
	logMsg = "enabled back the file logger, so this line will be printed to file:" + fullFileName;
	stdoutAndFileLogger.MyLoggerEnableOutputDestination(MY_LOGGER_FILE);
	stdoutAndFileLogger.Info(logMsg);
	cout << funcName + "END" << endl;
}

void createLoggerForStdoutOnlyWithClassThatSetItsOwnTagExample()
{
	const string funcName = "createLoggerForStdoutOnlyWithClassThatSetItsOwnTagExample - ";
	cout << funcName + "START" << endl;

	// By default the BasicLogger outputs message only to stdout
	// and is set to log level INFO
	const string fileName = "exampleFile.txt";
	const filesystem::path cwdPath= std::filesystem::current_path(); 
    cout << funcName + "current working directory is:" << cwdPath.c_str() << endl;
    filesystem::path fullPath = cwdPath;
    fullPath /= fileName;
	cout << funcName + "creating logger for both stdout and file:" << fullPath.c_str() << endl;
	
	// Make sure there is no file from previous execution
	if (filesystem::exists(filesystem::path(fullPath.c_str())))
	{
		cout << "removing file:" << fullPath.c_str() << " from prev runs" << endl;
		remove(fullPath.c_str());
	}

	BasicLogger basicLogger(fullPath.c_str());
	string logMsg = "this is the first log message for the class with its own tag sample";
	basicLogger.Info(logMsg);

	SampleClassWithBasicLog c;
	c.InitLog(&basicLogger);
	c.someFunc();
	c.someFuncThatWriteTextFormatMessage();
	cout << funcName + "END" << endl;
}

void createLoggerForStdoutAndFileAndMemory()
{
	const string funcName = "createLoggerForStdoutAndFileAndMemory - ";
	cout << funcName + "START" << endl;

	// By default the BasicLogger outputs message only to stdout
	// and is set to log level INFO
	const string fileName = "exampleFile.txt";
	const filesystem::path cwdPath= std::filesystem::current_path(); 
    cout << funcName + "current working directory is:" << cwdPath.c_str() << endl;
    filesystem::path fullPath = cwdPath;
    fullPath /= fileName;
	cout << funcName + "creating logger for both stdout and file:" << fullPath.c_str() << endl;
	
	// Make sure there is no file from previous execution
	if (filesystem::exists(filesystem::path(fullPath.c_str())))
	{
		cout << "removing file:" << fullPath.c_str() << " from prev runs" << endl;
		remove(fullPath.c_str());
	}

	BasicLogger basicLogger(fullPath.c_str());
	string logMsg = "first line will NOT go to memory";
	basicLogger.Info(logMsg);

	// Now create a "user specific" memory logger and add it to the "main logger"
	ILogMessageObserver* memLoggerPtr = new BasicMemoryLogger();
	basicLogger.Attach(memLoggerPtr, MY_LOGGER_MEMORY);
	logMsg = "this line will appear also in memory log";
	basicLogger.Info(logMsg);
	cout << funcName + "END" << endl;
} 

/*
This is the entry point for a sample application that utilizes the
different logger capabilities. Uncomment (and re-compile) the desired
sample method you wish to run.
*/
int main(int argc, char** argv)
{
	cout << "main - start" << endl;
	if (argc > 1)
	{
		string arg1 = argv[1];
	}
	
	//createLoggerForStdoutOnlyExample();
	//createLoggerForStdoutAndFileExample();
	//createLoggerForStdoutOnlyWithClassThatSetItsOwnTagExample();
	createLoggerForStdoutAndFileAndMemory();

	cout << "main - end" << endl;
	return 0;
}
