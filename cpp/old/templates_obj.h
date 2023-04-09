#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "template_obj.h"
#include "template_keys.h"
#include "conform_path.h"

#ifndef TEMPLATES_OBJ_H
#define TEMPLATES_OBJ_H

class Templates
{

public:
	// prototypes
	Templates(std::map<std::string, std::map<std::string, std::string>> templatePaths, 
		      std::map<std::string, std::map<std::string, std::map<std::string, std::string>>> templateKeys);

	// accesseurs
	std::map<std::string, TemplatePath> getTemplates();

private:

	std::map<std::string, std::map<std::string, std::string>> _templates_path;
	std::map<std::string, std::map<std::string, std::map<std::string, std::string>>> _templates_keys;

	std::map<std::string, std::map<std::string, std::map<std::string, std::string>>> _all_templates;
	// ConformPath _conform_path(std::map<std::string, std::map<std::string, std::string>>);

	std::vector <TemplateKey> listOfALlKeys();

};

#endif // TEMPLATES_OBJ_H