#include "unishare.hpp"
#include "app.hpp"
#include <string>
#include "settings.hpp"
#include <Windows.h>

int main(int argc, char* args[])
{
	Settings settings("unishare.ini");
	USError result = settings.readIniFile();
	CHECK_RESULT;

	Application* app = nullptr;
	if (argc > 1 && strcmp(args[1], "server") == 0)
		app = new UnishareServerApp(&settings);
	else
		app = new UnishareClientApp(&settings);

	HeapGuard<Application> g(app);

	return app->run();
}