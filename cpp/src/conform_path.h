#pragma once

#include <map>
#include <string>
#include <iostream>
#include <algorithm>
#include "utils.h"
#include "template_keys.h"

class ConformPath
{

public:

	// prototypes
	ConformPath(std::map<std::string, std::map<std::string, std::string>>);

	// accesseurs
	std::string buildDefinitionPath(std::string path);

	// manipulateurs
	//...

private:

	std::map<std::string, std::map<std::string, std::string>> _templatePaths;
	std::string _getDefinitions(std::string);
	std::string _getStringDefinitions(std::string);
};