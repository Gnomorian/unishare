#include "unishare.h"
#include "application.h"
#include "errors.h"

int main(int argc, char* args[])
{
	Application* app = nullptr;
	if (argc > 1 && strcmp(args[1], "server") == 0)
		app = new UnishareServerApp();
	else
		app = new UnishareClientApp();

	HeapGuard<Application> g(app);

	const int result = app->run();
	if(result != US_OK)
		errorHandler.printCallstack();
	return result;
}