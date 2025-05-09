#pragma once

#include <map>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <utility> // pour std::pair
#include <filesystem>
#include <yaml-cpp/yaml.h>

// template <typename TypeList>

std::string getOSSeparator();
std::string removePatternInString(std::string patternStr, std::string search, std::string replacement);
std::string removeSpaceInString(std::string);
std::string matchSeparator(std::string);
std::string dirNameFromString(const std::string);
std::vector<std::string> splitPath(const std::string&);
std::vector<std::string> pathListDir(std::string);
std::string joinListWithSeparator(std::vector<std::string>, char);
std::string stringPathJoin(const std::string&, const std::string&, const std::string&, const std::string&);
std::pair<std::string, std::string> getKeyValueFromString(std::string);
std::map<std::string, std::string> generateStringsDictionnaryFromString(std::string);
std::map<std::string, std::string> generatePathsDictionnaryFromString(std::string);
std::map<std::string, std::map<std::string, std::string>> generateKeysDictionnaryFromString(std::string);
std::vector<std::string>listFilesFromPathPattern(const std::string, std::string);
std::vector<std::string> listFromString(std::string);
std::string removeLeadingSlash(const std::string&);
std::vector<std::string> walkDir(std::string directory);
void addElementToList(std::vector<std::string>& myList, const std::string& elementToAdd);
// void addElementToList(std::vector<TypeList>& myList, const TypeList& elementToAdd);
bool isDir(const std::string& path);
bool isFile(const std::string& path);
bool isDirExist(std::string path);
bool isFileExist(std::string path);
void processNode(const YAML::Node& node, const std::string& indent);