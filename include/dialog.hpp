#pragma once

#include <string>

class LoginDialog
{
public:
	std::string username;
	std::string password;

	// returns true if they filled out, false if they canceled in some way
	bool show();
};