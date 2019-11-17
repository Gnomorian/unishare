#pragma once

#include "unishare.hpp"
#include "net.hpp"
#include <vector>
#include "settings.hpp"

class Application
{
protected:
	bool running;
	Settings* settings;
public:
	Application(Settings* settings) : running(true), settings(settings) {}

	virtual USError init() = 0;
	virtual USError update() = 0;
	virtual USError run() final
	{
		USError result = init();

		while (result == OK)
			result = update(); 

		return result;
	}
};

class UnishareClientApp : public Application
{
	Socket socket;
public:
	UnishareClientApp(Settings* settings) : Application(settings) {}
	~UnishareClientApp() = default;

	USError init() override;
	USError update() override;
};

class UnishareServerApp : public Application
{
	Socket socket;
	std::vector<Socket*> clients;
public:
	UnishareServerApp(Settings* settings) : Application(settings) {};
	~UnishareServerApp() = default;

	USError init() override;
	USError update() override;
};