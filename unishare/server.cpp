#include "app.hpp"
#include <iostream>
#include "settings.hpp"

USError UnishareServerApp::init()
{
	USError result = socket.init();
	CHECK_RESULT;

	try
	{
		socket.set(settings->settings.at("server:host"), settings->settings.at("server:port"));
	}
	catch (const std::out_of_range & oor)
	{
		std::cout << oor.what() << std::endl;
		std::cout << "settings server:host or server:port is missing!" << std::endl;
		std::cout << "settings dump:" << std::endl;
		settings->print();
	}

	return socket.bind();
}

USError UnishareServerApp::update()
{
	Socket remote;
	USError result = socket.accpet(remote);
	CHECK_RESULT;

	std::string data;
	result = remote.recieve(data);
	CHECK_RESULT;

	std::cout << "Client Said: " << data << std::endl;

	result = remote.send("Hello client, im the server!");
	CHECK_RESULT;

	return ApplicationDone;
}