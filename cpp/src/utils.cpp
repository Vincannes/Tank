#include <map>
#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <sstream>
#include <algorithm>
#include <utility> // pour std::pair
#include <filesystem>
#include <sys/stat.h>

#include "utils.h"

struct stat s;

// template <typename TypeList>

std::string getOSSeparator()
{
	std::string windowsSlash = "\\";
	std::string linuxSlash   = "/";
	#if defined(_WIN32)
		return windowsSlash;
	#else
		return linuxSlash;
	#endif
}

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
	std::string replacement = "/";
	return removePatternInString(patternStr, search, replacement);
}

std::vector<std::string> splitPath(const std::string& path) {
	char delimiter = '/';
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

std::string removeLeadingSlash(const std::string& input) {
    if (!input.empty() && input[0] == '/') {
        return input.substr(1); // Retourne la chaîne sans le premier caractère
    } else {
        return input; // Retourne la chaîne inchangée
    }
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
	std::string result_path = path1;
	result_path = result_path + "/" + removeLeadingSlash(path2);
    if (!path3.empty())
    {
        result_path = result_path + "/" + removeLeadingSlash(path3);
    }
    if (!path4.empty())
    {
        result_path = result_path + "/" + removeLeadingSlash(path4);
    }
    return removePatternInString(result_path, "/", getOSSeparator());
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

std::map<std::string, std::string> generatePathsDictionnaryFromString(std::string config_path){

    std::map<std::string, std::string> pathsDict;

	YAML::Node config = YAML::LoadFile(config_path);
	const YAML::Node& pathsNodes = config["paths"];

    for (const auto& pathNode : pathsNodes) {
        std::string pathName = pathNode.first.as<std::string>();
        std::string path = pathNode.second.as<std::string>();
        pathsDict[pathName] = path;
    }

	return pathsDict;
}

std::map<std::string, std::map<std::string, std::string>> generateKeysDictionnaryFromString(std::string config_path){
	std::map<std::string, std::map<std::string, std::string>> result;

	YAML::Node config = YAML::LoadFile(config_path);
	const YAML::Node& keysNode = config["keys"];

    for (const auto& keyNode : keysNode) {
        std::string keyName = keyNode.first.as<std::string>();

        if (keyNode.second.IsMap()) {

            for (const auto& element : keyNode.second) {
                std::string subKeyName = element.first.as<std::string>();
                std::string subKeyValue = "";

                if(subKeyName == "choices") {
                    const YAML::Node& choicesNode = element.second;
                    std::stringstream choicesString;
                    for (std::size_t i = 0; i < choicesNode.size(); ++i) {
                        choicesString << choicesNode[i].as<std::string>();
                        if (i < choicesNode.size() - 1) {
                            choicesString << ", ";
                        }
                    }
                    subKeyValue = choicesString.str();
                } else{
                    subKeyValue = element.second.as<std::string>();
                }
                result[keyName][subKeyName] = subKeyValue;
            }
        }
    }

	return result;
}

std::map<std::string, std::string> generateStringsDictionnaryFromString(std::string config_path)
{
	std::map<std::string, std::string> stringsOutput;

    YAML::Node config = YAML::LoadFile(config_path);
	const YAML::Node& pathsNodes = config["strings"];

    for (const auto& pathNode : pathsNodes) {
        std::string pathName = pathNode.first.as<std::string>();
        std::string path = pathNode.second.as<std::string>();
        stringsOutput[pathName] = path;
    }

    return stringsOutput;
}

std::vector<std::string> walkDir(std::string directory)
{
	std::vector<std::string> results;

    for (const auto& entry : std::filesystem::recursive_directory_iterator(directory)) {
        results.push_back(entry.path().string());
    }
	return results;
}

std::vector<std::string> listFilesFromPathPattern(const std::string directory, std::string origpatternStr) {
    
	std::vector<std::string> matchingFiles;

	std::string patternStr = origpatternStr;
	std::string directory_path = directory;
	#if defined(_WIN32)
		patternStr     = removePatternInString(origpatternStr, "/", "\\\\"); // Matching Windows
		directory_path = removePatternInString(directory, "/", "\\");        // Matching Windows
	#endif

	patternStr = removePatternInString(patternStr, "\\", "\\\\");
	std::filesystem::path dirPath(directory_path);
	std::regex regexPattern(patternStr);

	std::vector<std::string> dirs = walkDir(directory_path);
	for(int i = 0; i < dirs.size(); i++) {
		std::string path = dirs[i];
		if(std::regex_match(path, regexPattern)){
			matchingFiles.push_back(path);
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

void addElementToList(std::vector<std::string>& myList, const std::string& elementToAdd) {
    bool elementExists = false;
    for (const std::string& item : myList) {
        if (item == elementToAdd) {
            elementExists = true;
            break;
        }
    }

    if (!elementExists) {
        myList.push_back(elementToAdd);
    }
}

bool isDir(const std::string& path) {
    //std::error_code ec;
    //return std::filesystem::is_directory(path, ec);
	if(isFile(path)){
		return false;
	}
	else if(path.empty() && (!path.back() == '/' || !path.back() == '\\')){
		return false;
	}
	return true;
}

bool isFile(const std::string& path) {
	//std::error_code ec;
    //return std::filesystem::is_regular_file(path, ec);
	const std::string extensionRegex = "\\.[a-zA-Z0-9]+";
	std::regex regexPattern(extensionRegex);
    return std::regex_search(path, regexPattern);
}

bool isDirExist(std::string path) {

	const char* path_char = path.c_str();

    struct stat info;
    if (stat(path_char, &info) != 0) {
        std::perror("Erreur: ");
        return false;
    }

    return S_ISDIR(info.st_mode);
}

bool isFileExist(std::string path) {

	const char* path_char = path.c_str();

	struct stat info;
    if (stat(path_char, &info) != 0) {
        std::perror("Erreur: ");
        return false;
    }

    return S_ISREG(info.st_mode);
}

void processNode(const YAML::Node& node, const std::string& indent="") {
    if (node.IsScalar()) {
        std::cout << indent << "value: " << node.as<std::string>() << std::endl;
    } else if (node.IsMap()) {
        for (const auto& pair : node) {
            std::cout << indent << "key : " << pair.first.as<std::string>() << std::endl;
            processNode(pair.second, indent + "  "); // Appel récursif pour traiter la valeur
        }
    } else if (node.IsSequence()) {
        for (const auto& element : node) {
            processNode(element, indent + "- "); // Ajouter un préfixe "- " pour indiquer un élément de séquence
        }
    }
}