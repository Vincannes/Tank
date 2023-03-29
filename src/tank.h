#pragma once

#include "template_keys.h"
#include "templates_obj.h"

class Tank
{
public:
	Tank(std::string configPath);
	//std::map<std::string, std::map<std::string, std::string>> pathsdict;
	//std::map<std::string, std::map<std::string, std::map<std::string, std::string>>> keydict;
	//std::map<std::string, Template> templates;

private:

	std::string _configPath;
	/*
	Templates& _templatesObj(std::map<std::string, std::map<std::string, std::string>> pathsdict, 
		std::map<std::string, std::map<std::string, std::map<std::string, std::string>>> keydict);
		*/
	//Templates 
};

