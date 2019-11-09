#include "unishare.h"
#include "application.h"
#include "errors.h"

ErrorHandler* ErrorHandler::instance = nullptr;

int main(int argc, char* args[])
{
	ErrorHandler::instance = new ErrorHandler;
	HeapGuard<ErrorHandler> errorHandlerGuard(ErrorHandler::instance);

	Application* app = nullptr;
	if (argc > 1 && strcmp(args[1], "server") == 0)
		app = new UnishareServerApp();
	else
		app = new UnishareClientApp();

	HeapGuard<Application> g(app);

	const int result = app->run();
	if(result != US_OK)
		ErrorHandler::instance->printCallstack();
	return result;
}