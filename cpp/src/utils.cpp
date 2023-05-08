#include <map>
#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <sstream>
#include <algorithm>
#include <utility> // pour std::pair
#include <filesystem>

#include "utils.h"

std::string removePatternInString(std::string patternStr, std::string search, std::string replacement)
{
	size_t pos = 0;
    while ((pos = patternStr.find(search, pos)) != std::string::npos) {
        patternStr.replace(pos, search.length(), replacement);
        pos += replacement.length();
    }
	return patternStr;
}

std::string matchSeparator(std::string patternStr)
{
	std::string search = "\\";
    // std::string replacement = "\\\\";
	std::string replacement = "/";
	return removePatternInString(patternStr, search, replacement);
}

std::vector<std::string> splitPath(const std::string& path) {
	char delimiter = '/';
	// char delimiter = '\\';
	// std::string delimiter = os::sep;

	std::vector<std::string> result;
	std::stringstream ss(path);
	std::string token;
	while (std::getline(ss, token, delimiter)) {
		result.push_back(token);
	}
	return result;
}

std::string dirNameFromString(const std::string path)
{
	std::filesystem::path filePath(path);
	std::string directoryPath = filePath.parent_path().string();
	return directoryPath;
}

std::vector<std::string> pathListDir(std::string directory)
{
	std::vector<std::string> dirs;
	std::filesystem::path dirPath(directory);

	for (const auto& entry : std::filesystem::directory_iterator(dirPath)) {
        const auto& path = entry.path();
        if (std::filesystem::is_directory(path)) {
            // Directory found, recursively traverse
            // std::cout << "Directory: " << path << std::endl;
            listFilesFromPathPattern(path.string(), "");
        } else if (std::filesystem::is_regular_file(path)) {
            // std::cout << "File: " << path << std::endl;
        }
    }
	return dirs;
}

std::string removeSpaceInString(std::string str)
{
	str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
	return str;
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

std::string stringPathJoin(const std::string& path1, const std::string& path2, const std::string& path3="", const std::string& path4="")
{
	std::filesystem::path result_path = path1;
    result_path /= path2;
    if (!path3.empty())
    {
        result_path /= path3;
    }
    if (!path4.empty())
    {
        result_path /= path4;
    }
    return result_path.string();
}

std::pair<std::string, std::string> getKeyValueFromString(std::string pathToParse)
{
	std::string stringToParse = matchSeparator(pathToParse);
    std::string::size_type colonPos = stringToParse.find(":");
    std::string key = stringToParse.substr(0, colonPos);
    std::string value = stringToParse.substr(colonPos + 1);
    key.erase(0, 1);
    key.erase(key.size() - 1, 1);
    if (key.find("/") != std::string::npos) {
        key.erase(0, 1);
    }
	value = removePatternInString(value, "'", "");
	value = removeSpaceInString(value);
    return std::make_pair(key, value);
}

std::map<std::string, std::string> generatePathsDictionnaryFromString(std::string templatesStr){

    std::map<std::string, std::string> pathsDict;

    // Supprime les accolades de la chaîne de caractères
    templatesStr.erase(0, 1);
    templatesStr.erase(templatesStr.size() - 1, 1);

    // Parcourt la chaîne de caractères pour extraire les clés et les valeurs
    std::string::size_type pos = 0, prev = 0;
    while ((pos = templatesStr.find(",", pos + 1)) != std::string::npos) {
        std::string pair = templatesStr.substr(prev, pos - prev);
        auto result = getKeyValueFromString(pair);
		std::string key = removePatternInString(result.first, "'", "");
        pathsDict[key] = result.second;
        prev = pos + 1;
    }

    // Ajoute la dernière paire clé/valeur
    std::string pair = templatesStr.substr(prev);
    auto result = getKeyValueFromString(pair);
	std::string last_key = removePatternInString(result.first, "'", "");
    pathsDict[last_key] = result.second;
    return pathsDict;
}

std::map<std::string, std::map<std::string, std::string>> generateKeysDictionnaryFromString(std::string templatesStr){
    
	std::map<std::string, std::map<std::string, std::string>> keysDict;

	// Supprime les accolades de la chaîne de caractères
	templatesStr = removeSpaceInString(templatesStr);
    templatesStr.erase(0, 1);
    templatesStr.erase(templatesStr.size() - 1, 1);
    
	std::regex regex_splited("\\},'"); // splited at }, '
	std::sregex_token_iterator iter(templatesStr.begin(), templatesStr.end(), regex_splited, -1);
    std::sregex_token_iterator ende;

    for (; iter != ende; ++iter) {
		std::string keystring = *iter ;
		std::string::size_type colonPos = keystring.find(":");

		std::string key          = keystring.substr(0, colonPos);
		std::string value        = keystring.substr(colonPos + 1);

		key.erase(std::remove(key.begin(), key.end(), '\''), key.end()); // Remove ' from string
		value.erase(std::remove(value.begin(), value.end(), '{'), value.end()); // Remove { from string
		value.erase(std::remove(value.begin(), value.end(), '}'), value.end()); // Remove } from string		

		// if list in value, ie: "choices" = ['..', '..'] 
		std::smatch match;
		std::string valueRefacto = value;
		std::regex re("\\[([^\\]]*)\\]");
  		std::vector<std::string> choices;
		while (std::regex_search(valueRefacto, match, re)) {
			std::string match_refacto = match[1].str();
			match_refacto.erase(std::remove(match_refacto.begin(), match_refacto.end(), '\''), match_refacto.end());
			choices.push_back(match_refacto);
			valueRefacto = match.suffix().str();
			value = std::regex_replace(value, std::regex("\\[[^\\]]*\\]"), ""); // remove ['..', '..']
			value = std::regex_replace(value, std::regex(", 'choices':"), "");  // remove 'choices'
		}

		// Parse all other element for each ','
    	std::string item;
		std::stringstream ss(value);
		while (std::getline(ss, item, ',')) {
			std::string::size_type colonPosValue = item.find(":");
			std::string keyValue = item.substr(0, colonPosValue);
			std::string valValue = item.substr(colonPosValue+1);
			keyValue.erase(std::remove(keyValue.begin(), keyValue.end(), '\''), keyValue.end()); // Remove ' from string
			valValue.erase(std::remove(valValue.begin(), valValue.end(), '\''), valValue.end()); // Remove ' from string
			keyValue = removeSpaceInString(keyValue);
			valValue = removeSpaceInString(valValue);
			keysDict[key][keyValue] = valValue;
		}

		// add choices if exist as string
		std::string choice = joinListWithSeparator(choices, ',');
		if(!choice.empty()){
			keysDict[key]["choices"] = choice;
		}
	}
    return keysDict;
}

std::map<std::string, std::string> generateStringsDictionnaryFromString(std::string templatesStr)
{
	std::map<std::string, std::string> stringsOutput;
	// Supprime les accolades de la chaîne de caractères
    templatesStr.erase(0, 1);
    templatesStr.erase(templatesStr.size() - 1, 1);

	// Parcourt la chaîne de caractères pour extraire les clés et les valeurs
    std::string::size_type pos = 0, prev = 0;
	while ((pos = templatesStr.find(",", pos + 1)) != std::string::npos) {
        std::string pair = templatesStr.substr(prev, pos - prev);
        auto result      = getKeyValueFromString(pair);
		std::string key  = removePatternInString(result.first, "'", "");
        stringsOutput[key] = result.second;
        prev = pos + 1;
    }

	// Ajoute la dernière paire clé/valeur
	try{
		std::string pair     = templatesStr.substr(prev);
		auto result          = getKeyValueFromString(pair);
		std::string last_key = removePatternInString(result.first, "'", "");
		stringsOutput[last_key] = result.second;
	}
	catch(const std::exception& e) {}
	return stringsOutput;
}

std::vector<std::string> listFilesFromPathPattern(const std::string directory, std::string origpatternStr) {
    
	std::vector<std::string> matchingFiles;
	std::string patternStr = removePatternInString(origpatternStr, "/", "\\\\"); // Matching Windows
	std::string directory_path = removePatternInString(directory, "/", "\\"); // Matching Windows

	std::filesystem::path dirPath(directory_path);
	std::regex regexPattern(patternStr);

	for (const auto& entry : std::filesystem::directory_iterator(dirPath)) {
        const auto& path = entry.path();
        if (std::filesystem::is_directory(path)) {
			for (const auto& path : listFilesFromPathPattern(path.string(), origpatternStr)){
            	matchingFiles.push_back(path);
			}
        } else if (std::filesystem::is_regular_file(path)) {
			if(std::regex_match(path.string(), regexPattern)){
            	matchingFiles.push_back(path.string());
			}
        }
    }

    return matchingFiles;
}

std::vector<std::string> listFromString(std::string str)
{
	std::vector<std::string> list;
    std::stringstream ss(str);

    std::string item;
    while (std::getline(ss, item, ',')) {
        // Retirer les espaces vides au début et à la fin de l'élément
        item.erase(0, item.find_first_not_of(" "));
        item.erase(item.find_last_not_of(" ") + 1);
        
        list.push_back(item);
    }
	return list;
}
