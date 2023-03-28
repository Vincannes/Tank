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
			std::string ele_path = _getDefinitions(s);
			_definitions.push_back(ele_path);
		}
		else {
			_definitions.push_back(s);
		}
	}
	return joinListWithSeparator(_definitions, '\\');

}


std::string ConformPath::_getDefinitions(std::string element) {

	std::string element_key_name = element.erase(element.find("@"), 1);
	std::string ele_path = this->_templatePaths["paths"][element_key_name];

	std::vector<std::string> ele_path_list;
	std::vector<std::string> definitionSplited = splitPath(ele_path);

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

	return joinListWithSeparator(ele_path_list, '\\');;
}