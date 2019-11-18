#define UNISHARE_COMMON
#include "settings.hpp"
#include <regex>
#include <iostream>

inline std::string toLower(const std::string& source)
{
	std::string buffer(std::ref(source));
	for (auto& c : buffer)
		c = std::tolower(c);
	return buffer;
}

USError Settings::readIniFile()
{
#pragma region get file contents
	FILE* file = nullptr;
	int result = fopen_s(&file, fileName.c_str(), "r");
	fseek(file, 0, SEEK_END);
	auto length = ftell(file);
	rewind(file);
	std::string buffer;
	buffer.assign(length, '\0');
	fread(const_cast<char*>(buffer.data()), sizeof(char), length, file);
	if (result != OK) return UnknownError;
#pragma endregion

	std::regex re(regexString, std::regex::ECMAScript);
	std::smatch match;

	std::string currentGroup;
	std::string searchMe(buffer);

	while (std::regex_search(searchMe, match, re))
	{
		if (match[1].matched)
			currentGroup = toLower(match[2].str());

		std::string key	  = toLower(match[4].str());
		std::string value = toLower(match[5].str());

		settings[currentGroup + ":" + key] = value;
		searchMe = match.suffix();
	}

	return OK;
}