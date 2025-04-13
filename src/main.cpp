#include <filesystem>
#include <iostream>

#include "logger/basicLogger.h"

using namespace std;

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
	BasicLogger basicLogger;
	string logMsg = "this is the first log message for the class with its own tag sample";
	basicLogger.Info(logMsg);
	cout << funcName + "END" << endl;
} 
/*
This is the entry point for a sample application that utilizes the
different logger capabilities. Uncomment the desired sample method
you wish to run.
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
	createLoggerForStdoutOnlyWithClassThatSetItsOwnTagExample();
	cout << "main - end" << endl;
	return 0;
}
