#include <map>
#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <sstream>
#include <utility> // pour std::pair

#include "utils.h"


std::vector<std::string> splitPath(const std::string& path) {
	char delimiter = '\\';
	// std::string delimiter = os::sep;

	std::vector<std::string> result;
	std::stringstream ss(path);
	std::string token;
	while (std::getline(ss, token, delimiter)) {
		result.push_back(token);
	}
	return result;
}


std::string joinListWithSeparator(std::vector<std::string> list, char separator) {
	std::string result = "";
	for (int i = 0; i < list.size(); i++) {
		if (i > 0) {
			result += separator;
		}
		result += list[i];
	}
	return result;
}


std::pair<std::string, std::string> getKeyValueFromString(std::string stringToParse)
{
    std::string::size_type colonPos = stringToParse.find(":");
    std::string key = stringToParse.substr(0, colonPos);
    std::string value = stringToParse.substr(colonPos + 1);
    key.erase(0, 1);
    key.erase(key.size() - 1, 1);
    if (key.find('\'') != std::string::npos) {
        key.erase(0, 1);
    }
    value.erase(0, 2);
    value.erase(value.size() - 1, 2);
    return std::make_pair(key, value);
}


std::map<std::string, std::map<std::string, std::string>> generatePathsDictionnaryFromString(std::string yamlStr){

    std::map<std::string, std::map<std::string, std::string>> pathsDict;

    // Supprime les accolades de la chaîne de caractères
    yamlStr.erase(0, 1);
    yamlStr.erase(yamlStr.size() - 1, 1);

    // Parcourt la chaîne de caractères pour extraire les clés et les valeurs
    std::string::size_type pos = 0, prev = 0;
    while ((pos = yamlStr.find(",", pos + 1)) != std::string::npos) {
        std::string pair = yamlStr.substr(prev, pos - prev);
        auto result = getKeyValueFromString(pair);
        pathsDict["paths"][result.first] = result.second;
        prev = pos + 1;
    }

    // Ajoute la dernière paire clé/valeur
    std::string pair = yamlStr.substr(prev);
    auto result = getKeyValueFromString(pair);
    pathsDict["paths"][result.first] = result.second;
    return pathsDict;
}


std::map<std::string, std::map<std::string, std::map<std::string, std::string>>> generateKeysDictionnaryFromString(std::string yamlStr){
    std::map<std::string, std::map<std::string, std::map<std::string, std::string>>> keysDict;

	// Supprime les accolades de la chaîne de caractères
    yamlStr.erase(0, 1);
    yamlStr.erase(yamlStr.size() - 1, 1);
    
	std::regex regex_splited("\\}, '"); // splited at }, '
	std::sregex_token_iterator iter(yamlStr.begin(), yamlStr.end(), regex_splited, -1);
    std::sregex_token_iterator ende;

    for (; iter != ende; ++iter) {
		std::string keystring = *iter ;
		std::string::size_type colonPos = keystring.find(":");

		std::string key = keystring.substr(0, colonPos);
		std::string value = keystring.substr(colonPos + 1);

		key.erase(std::remove(key.begin(), key.end(), '\''), key.end()); // Remove ' from string
		value.erase(std::remove(value.begin(), value.end(), '{'), value.end()); // Remove { from string
		value.erase(std::remove(value.begin(), value.end(), '}'), value.end()); // Remove } from string

		std::vector<std::string> result;
		std::stringstream ss(value);
    	std::string item;

		while (std::getline(ss, item, ',')) {
			std::string::size_type colonPosValue = item.find(":");
			std::string keyValue = item.substr(0, colonPosValue);
			std::string valValue = item.substr(colonPosValue+1);
			keyValue.erase(std::remove(keyValue.begin(), keyValue.end(), '\''), keyValue.end()); // Remove ' from string
			valValue.erase(std::remove(valValue.begin(), valValue.end(), '\''), valValue.end()); // Remove ' from string
			keysDict["keys"][key][keyValue] = valValue;
		}
	}
    return keysDict;
}

