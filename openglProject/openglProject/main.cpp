// main.cpp is the entry poin to
// the OpenGL application.

// Include headers
#include "Application.h"

// namespace declaration
using namespace applicationFramework;

// Main function to the application
int main(int argc, char *argv[])
{
	// Create application instance
	Application application;
	application.setLookAt(0.0, 2.0, 10.0, 0.0, 2.0, 0.0, 0.0, 1.0, 0.0);
	application.startApplication(argc, argv);

	// **Note** No code below startFramework() will get executed 

	return 0;
}