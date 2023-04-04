#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "templates_obj.h"
#include "template_keys.h"

Templates::Templates(std::map<std::string, std::map<std::string, std::string>> templatePaths, 
	std::map<std::string, std::map<std::string, std::map<std::string, std::string>>> templateKeys)
{
	this->_templates_path = templatePaths;
	this->_templates_keys = templateKeys;
	this->templates       = getTemplates();
	this->_conform_path(_templates_path);
}

ConformPath Templates::_conform_path(std::map<std::string, std::map<std::string, std::string>>)
{
	return ConformPath(this->_templates_path);
}

std::vector<TemplateKey> Templates::listOfALlKeys()
{
	std::vector <TemplateKey> keysList{};
	std::map<std::string, std::map<std::string, std::string>> pathsdict;

	for (auto outerIt = this->_templates_keys["keys"].begin(); outerIt != this->_templates_keys["keys"].end(); ++outerIt) {

		bool isType;
		bool isDefault;
		std::string isTypeValue = "";
		std::string isDefaultValue = "";
		std::string name = outerIt->first;

		for (auto innerIt = outerIt->second.begin(); innerIt != outerIt->second.end(); ++innerIt) {
			std::string key = innerIt->first;
			std::string value = innerIt->second;
			if (key == "type") {
				isType = true;
				isTypeValue = value;
			}
			else if (key == "default") {
				isDefault = true;
				isDefaultValue = value;
			}
		}
		if (isTypeValue == "str") {
			StringKey s1(name, isDefaultValue);
			keysList.push_back(s1);
		}
		if (isTypeValue == "int") {
			IntegerKey t1(name, isDefaultValue);
			keysList.push_back(t1);
		}
	}

	return keysList;
}


std::map<std::string, Template> Templates::getTemplates() {

	std::map<std::string, Template> templates;
	std::vector<TemplateKey> keysList = listOfALlKeys();

	for (auto outerIt = this->_templates_path["paths"].begin(); outerIt != this->_templates_path["paths"].end(); ++outerIt) {
		std::string template_name = outerIt->first;
		std::string template_path = this->_templates_path["paths"][template_name];
		Template templateObj(template_name, keysList, template_path);
		templates.insert(std::make_pair(template_name, templateObj));
	}
	return templates;
}
