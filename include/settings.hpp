#pragma once

#include "unishare.hpp"
#include <string>
#include <map>
#include <iostream>

class DllExport Settings
{
	// optional [category] and option = result
	const char* regexString = R"((\[([^\[\]]+)\])?[\s]*(([\S]+[^\[][\S]+)\s*=\s*(\S+)))";
	std::string fileName;
public:
	std::map<std::string, std::string> settings;

	Settings(const std::string& fileName) : fileName(fileName) {}
	USError readIniFile();

	void print()
	{
		int count = 0;
		for (auto pair : settings)
			std::cout << "\t" << ++count << ") " << pair.first << "\t : \t" << pair.second << std::endl;
	}

};
