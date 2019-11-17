#include "app.hpp"
#include <string>
#include <iostream>

USError UnishareClientApp::init()
{
	USError result = socket.init();
	CHECK_RESULT;

	socket.set("localhost", "1234");

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