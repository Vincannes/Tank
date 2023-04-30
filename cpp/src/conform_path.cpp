#include "conform_path.h"

ConformPath::ConformPath(std::map<std::string, std::map<std::string, std::string>> templatePaths)
{
	this->_templatePaths = templatePaths;
}


std::string ConformPath::buildDefinitionPath(std::string path) {

	std::vector<std::string> splitedPath = splitPath(path);
	std::vector<std::string> _definitions;

	for (int i = 0; i < splitedPath.size(); i++) {

		std::string s = splitedPath[i];
		std::size_t pos = s.find('@');
		if (pos != std::string::npos) {
			std::string ele_path;
			
			// if "-" & "." in s 
			if (s.find('-') != std::string::npos || s.find('.') != std::string::npos) {
				// tokens.push_back(token);
				ele_path = _getStringDefinitions(s);
			}
			else{
				ele_path = _getDefinitions(s);
			}
			_definitions.push_back(ele_path);
		}
		else {
			_definitions.push_back(s);
		}
	}
	return joinListWithSeparator(_definitions, '/');

}


std::string ConformPath::_getDefinitions(std::string element) {

	std::string element_key_name = element.erase(element.find("@"), 1);
	std::string ele_path = this->_templatePaths["paths"][element_key_name];

	std::vector<std::string> ele_path_list;
	std::vector<std::string> definitionSplited = splitPath(ele_path);

	if(definitionSplited.size() > 0){
		for (int i = 0; i < definitionSplited.size(); i++) {
			std::size_t pos = definitionSplited[i].find('@');	
			if (pos != std::string::npos) {
				std::string test = _getDefinitions(definitionSplited[i]);
				ele_path_list.push_back(test);
			}
			else {
				ele_path_list.push_back(definitionSplited[i]);
			}
		}
	}
	else{
		ele_path_list.push_back(ele_path);
	}
	
	return joinListWithSeparator(ele_path_list, '/');;
}


std::string ConformPath::_getStringDefinitions(std::string stringParse)
{
	std::string stringDef = stringParse;
	std::vector<std::string> tokens;

    std::stringstream ss(stringParse);
	std::string token;

	while (std::getline(ss, token, '.') || std::getline(ss, token, '-')) {
		std::size_t pos = token.find('@');
		if (pos != std::string::npos) {
			std::string key_def = _getDefinitions(token);
			stringDef = removePatternInString(stringDef, token, key_def);
		}
	}

	return stringDef;
}