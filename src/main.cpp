#include <iostream>

#include "logger/basicLogger.h"

using namespace std;

void createLoggerForStdoutOnlyExample()
{
	const string funcName = "createLoggerForStdoutOnlyExample - ";
	cout << funcName + "START" << endl;
	BasicLogger basicLogger;

	cout << funcName + "END" << endl;
}

/*
This is the entry point for a sample application that utilizes the
different logger capabilities. 
*/
int main(int argc, char** argv)
{
	cout << "main - start" << endl;
	createLoggerForStdoutOnlyExample();
	cout << "main - end" << endl;
	return 0;
}
