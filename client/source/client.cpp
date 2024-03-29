#include "app.hpp"
#include <string>
#include <iostream>
#include "settings.hpp"
#include "dialog.hpp"

USError UnishareClientApp::init()
{
	USError result = socket.init();
	CHECK_RESULT;

	try
	{
		socket.set(settings->settings.at("client:host"), settings->settings.at("client:port"));
	}
	catch (const std::out_of_range & oor)
	{
		std::cout << oor.what() << std::endl;
		std::cout << "settings is missing an option!" << std::endl;
		std::cout << "settings dump:" << std::endl;
		settings->print();
	}

	return socket.connect();
}

USError UnishareClientApp::update()
{
	USError result = socket.send("Hello server!");
	CHECK_RESULT;

	std::string data;
	result = socket.recieve(data);
	CHECK_RESULT;

	std::cout << "Server Said: " << data << std::endl;

	return ApplicationDone;
}

USError UnishareClientApp::authenticate()
{
	LoginDialog dialog;
	dialog.show();

	return OK;
}