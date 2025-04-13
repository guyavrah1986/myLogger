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

	//cout << funcName + "END" << endl;
}

/*
This is the entry point for a sample application that utilizes the
different logger capabilities. 
*/
int main(int argc, char** argv)
{
	cout << "main - start" << endl;
	if (argc > 1)
	{
		string arg1 = argv[1];
	}
	
	createLoggerForStdoutOnlyExample();
	//cout << "main - end" << endl;
	return 0;
}
