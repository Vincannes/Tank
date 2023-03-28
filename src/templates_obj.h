#include <iostream>
#include <string>
#include <vector>
#include "template_obj.h"
#include "template_keys.h"
#include "conform_path.h"

class Templates {

public:
	Templates(std::map<std::string, std::map<std::string, std::string>> templatePaths, 
		std::map<std::string, std::map<std::string, std::map<std::string, std::string>>> templateKeys);

	std::map<std::string, Template> templates;


private:
	std::map<std::string, std::map<std::string, std::string>> _templates_path;
	std::map<std::string, std::map<std::string, std::map<std::string, std::string>>> _templates_keys;
	std::map<std::string, std::map<std::string, std::map<std::string, std::string>>> _all_templates;
	ConformPath _conform_path(std::map<std::string, std::map<std::string, std::string>>);

	std::vector <TemplateKey> listOfALlKeys();
	std::map<std::string, Template> getTemplates();

};

