#pragma once

#include "unishare.h"
#include "net.h"
#include "errors.h"

class Application
{
public:
	Application() = default;
	~Application() = default;

	virtual int run() { return US_OK; }
};

class UnishareServerApp : public Application
{
public:
	UnishareServerApp() {}
	~UnishareServerApp() {}

	int run() override;
};

class UnishareClientApp : public Application
{
	unishare::net::ClientSocket socket;
public:
	UnishareClientApp() {}
	~UnishareClientApp() {}

	int run() override;
};