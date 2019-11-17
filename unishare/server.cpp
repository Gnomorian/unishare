#include "app.hpp"
#include <iostream>

USError UnishareServerApp::init()
{
	USError result = socket.init();
	CHECK_RESULT;

	socket.set("localhost", "1234");

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