#pragma once

#include "unishare.hpp"
#include "net.hpp"
#include <vector>

class Application
{
protected:
	bool running;
public:
	Application() : running(true) {}

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
	UnishareClientApp() = default;
	~UnishareClientApp() = default;

	USError init() override;
	USError update() override;
};

class UnishareServerApp : public Application
{
	Socket socket;
	std::vector<Socket*> clients;
public:
	UnishareServerApp() = default;
	~UnishareServerApp() = default;

	USError init() override;
	USError update() override;
};