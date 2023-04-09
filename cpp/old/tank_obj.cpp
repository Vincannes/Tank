#include "tank_obj.h"
#include "utils.h"
//#include "template_obj.h"

Tank::Tank(std::string _templatePathsString, std::string _templateKeysString) 
{
    this->pathsdict            = generatePathsDictionnaryFromString(_templatePathsString);;
    this->keydict              = generateKeysDictionnaryFromString(_templateKeysString);
    this->_templates           = getTemplates();
    this->_allKeys             = listOfALlKeys();
}

std::map<std::string, TemplatePath> Tank::getTemplates()
{
    return this->_templates;
}


std::vector<TemplateKey> Tank::listOfALlKeys()
{
	std::vector <TemplateKey> keysList{};
	std::map<std::string, std::map<std::string, std::string>> pathsdict;

	for (auto outerIt = this->keydict["keys"].begin(); outerIt != this->keydict["keys"].end(); ++outerIt) {

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
			StringTemplateKey s1(name, isDefaultValue);
			keysList.push_back(s1);
		}
		if (isTypeValue == "int") {
			IntegerTemplateKey t1(name, isDefaultValue);
			keysList.push_back(t1);
		}
	}

	return keysList;
}


std::map<std::string, TemplatePath> Tank::_getTemplates(){

	std::map<std::string, TemplatePath> templates;
	//std::vector<TemplateKey> keysList = this->_allKeys;

	for (auto outerIt = this->pathsdict["paths"].begin(); outerIt != this->pathsdict["paths"].end(); ++outerIt) {
		std::string template_name = outerIt->first;
		std::string template_path = this->pathsdict["paths"][template_name];
		TemplatePath templateObj(template_name, this->_allKeys, template_path);
		templates.insert(std::make_pair(template_name, templateObj));
	}
	return templates;
}
