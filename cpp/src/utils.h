#pragma once

#include <map>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <utility> // pour std::pair
#include <filesystem>


std::string removeSpaceInString(std::string str);
std::string dirNameFromString(const std::string path);
std::vector<std::string> splitPath(const std::string& path);
std::vector<std::string> pathListDir(std::string directory);
std::string joinListWithSeparator(std::vector<std::string> list, char separator);
std::pair<std::string, std::string> getKeyValueFromString(std::string stringToParse);
std::map<std::string, std::map<std::string, std::string>> generatePathsDictionnaryFromString(std::string yamlStr);
std::map<std::string, std::map<std::string, std::map<std::string, std::string>>> generateKeysDictionnaryFromString(std::string yamlStr);
std::vector<std::string>listFilesFromPathPattern(std::string);
