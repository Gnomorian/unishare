#include "unishare.hpp"
#include "app.hpp"
#include <cstring>

int main(int argc, char* args[])
{
	Application* app = nullptr;
	if (argc > 1 && strcmp(args[1], "server") == 0)
		app = new UnishareServerApp();
	else
		app = new UnishareClientApp();

	HeapGuard<Application> g(app);

	return app->run();
}