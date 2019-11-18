#pragma once
#include <vector>
#include <string>
#include <filesystem>

class FileManager
{
	std::filesystem::path root;
public:
	FileManager(const std::string& rootDirectory)
	{
		root.assign(rootDirectory);
	}
	USError init();
};