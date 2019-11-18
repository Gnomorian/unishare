#include "app.hpp"
#include <iostream>
#include "settings.hpp"
#include "filemanager.hpp"

USError UnishareServerApp::init()
{
	USError result = socket.init();
	CHECK_RESULT;

	try
	{
		socket.set(settings->settings.at("server:host"), settings->settings.at("server:port"));
		fileManager = new FileManager(settings->settings["server:filesharedirectory"]);
	}
	catch (const std::out_of_range & oor)
	{
		std::cout << oor.what() << std::endl;
		std::cout << "Settings is missing an option!" << std::endl;
		std::cout << "settings dump:" << std::endl;
		settings->print();
	}

	result = fileManager->init();
	CHECK_RESULT;

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

USError FileManager::init()
{
	if (!std::filesystem::exists(root))
	{
		std::cout << "Root path \"" << root << "\" does not exist!" << std::endl;
		throw;
	}

	std::filesystem::recursive_directory_iterator itr(root);
	for (auto& p : itr)
	{
		std::cout << p.path() << std::endl;
	}
	return OK;
}